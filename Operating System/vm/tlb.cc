#include "copyright.h"
#include "tlb.h"
#include "syscall.h"
#include "machine.h"
#include "thread.h"
#include "system.h"
#include "utility.h"

//----------------------------------------------------------------------
// UpdateTLB
//      Called when exception is raised and a page isn't in the TLB.
// Figures out what to do (get from IPT, or pageoutpagein) and does it.
//----------------------------------------------------------------------

void UpdateTLB(int possible_badVAddr)
{
  int badVAddr;
  unsigned int vpn;
  int phyPage;

  if(possible_badVAddr) // get the bad address from the correct location
    badVAddr=possible_badVAddr; // fault in kernel
  else
    badVAddr=machine->registers[BadVAddrReg]; // fault in userprog

  vpn=(unsigned)badVAddr/PageSize;

  if((phyPage=VpnToPhyPage(vpn))!=-1)
    InsertToTLB(vpn, phyPage);
  else {
    if(vpn>=currentThread->space->numPages && !GetMmap(vpn))
      machine->RaiseException(AddressErrorException, badVAddr);      
    else
      InsertToTLB(vpn, PageOutPageIn(vpn));
 }
}

//----------------------------------------------------------------------
// VpnToPhyPage
//      Gets a phyPage for a vpn, if exists in ipt.
//----------------------------------------------------------------------

int VpnToPhyPage(int vpn)
{
	IptEntry* iptPtr = hashIPT(vpn,currentThread->pid);
	iptPtr = iptPtr->next;

	while(iptPtr != NULL) //Continue to check if current list node is not null
	{
		if((iptPtr->vPage == vpn) && (iptPtr->pid==currentThread->pid))
			return iptPtr->phyPage; //Return the physical page number if the virtual page number and the process id matches. A Hit
		iptPtr = iptPtr->next;		//Traverse the next List Node 
	}
  
	return -1; // Fault
}

//----------------------------------------------------------------------
// InsertToTLB
//      Put a vpn/phyPage combination into the TLB. If TLB is full, use FIFO 
//	replacement
//----------------------------------------------------------------------

void InsertToTLB(int vpn, int phyPage)
{
  int i = 0; //entry in the TLB
  
  while(i<TLBSize) // Continue to check if the entry have not hit the max TLBSize
  {
		if(machine->tlb[i].valid) //If the field is valid means it is active hence kept checking
			i++;
		else //If it not calid, means can be overwritten. Break out of while loop to get the corrent index
			break;
  }


  if(i == TLBSize)  //If the whole TLB table is occupied and set the victim field as the first entry
     i = FIFOPointer; 

 //Update the static FIFIO Pointer
  FIFOPointer = (i+1) % TLBSize; 

  // copy dirty data to memoryTable
  if(machine->tlb[i].valid){
    memoryTable[machine->tlb[i].physicalPage].dirty=machine->tlb[i].dirty;
    memoryTable[machine->tlb[i].physicalPage].TLBentry=-1;
  }

  //update the TLB entry
  machine->tlb[i].virtualPage  = vpn;
  machine->tlb[i].physicalPage = phyPage;
  machine->tlb[i].valid        = TRUE;
  machine->tlb[i].readOnly     = FALSE;
  machine->tlb[i].use          = FALSE;
  machine->tlb[i].dirty        = memoryTable[phyPage].dirty;

  //update the corresponding memoryTable
  memoryTable[phyPage].TLBentry=i;
  DEBUG('p', "The corresponding TLBentry for Page %i in TLB is %i ", vpn, i);
  //reset clockCounter to 0 since it is being used at this moment.
  //for the implementation of Clock algorithm.
  memoryTable[phyPage].clockCounter=0; 
}

//----------------------------------------------------------------------
// PageOutPageIn
//      Calls DoPageOut and DoPageIn and handles IPT and memoryTable
// bookkeeping. Use clock algorithm to find the replacement page.
//----------------------------------------------------------------------

int PageOutPageIn(int vpn)
{
  int phyPage; 
  IptEntry *iptPtr; 

  //increase the number of page faults
  stats->numPageFaults++;
  //call the clock algorithm, which returns the freed physical frame
  phyPage=clockAlgorithm();
  //Page out the victim page to free the physical frame
  DoPageOut(phyPage);
  //Page in the new page to the freed physical frame
  DoPageIn(vpn, phyPage);

  //make an entry in ipt
  iptPtr=hashIPT(vpn, currentThread->pid);
  while(iptPtr->next) iptPtr=iptPtr->next;
  iptPtr->next=new IptEntry(vpn, phyPage, iptPtr);
  iptPtr=iptPtr->next;
  
  //update memoryTable for this frame
  memoryTable[phyPage].valid=TRUE;
  memoryTable[phyPage].pid=currentThread->pid;
  memoryTable[phyPage].vPage=vpn;
  memoryTable[phyPage].corrIptPtr=iptPtr;
  memoryTable[phyPage].dirty=FALSE;
  memoryTable[phyPage].TLBentry=-1;
  memoryTable[phyPage].clockCounter=0;
  memoryTable[phyPage].swapPtr=currentThread->space->swapPtr;

 
  return phyPage;
}

//----------------------------------------------------------------------
// DoPageOut
//      Actually pages out a phyPage to it's swapfile.
//----------------------------------------------------------------------

void DoPageOut(int phyPage)
{
  MmapEntry *mmapPtr;
  int numBytesWritten;
  int mmapBytesToWrite;

  if(memoryTable[phyPage].valid){           // check if pageOut possible
    if(memoryTable[phyPage].TLBentry!=-1){
      memoryTable[phyPage].dirty=
	machine->tlb[memoryTable[phyPage].TLBentry].dirty;
      machine->tlb[memoryTable[phyPage].TLBentry].valid=FALSE;
    }
    if(memoryTable[phyPage].dirty){        // pageOut is necessary
      if((mmapPtr=GetMmap(memoryTable[phyPage].vPage))){ // it's mmaped
	DEBUG('p', "mmap paging out: pid %i, phyPage %i, vpn %i\n",
	      memoryTable[phyPage].pid, phyPage, memoryTable[phyPage].vPage);
	if(memoryTable[phyPage].vPage==mmapPtr->endPage)
	  mmapBytesToWrite=mmapPtr->lastPageLength;
	else
	  mmapBytesToWrite=PageSize;
	numBytesWritten=mmapPtr->openFile->
	  WriteAt(machine->mainMemory+phyPage*PageSize, mmapBytesToWrite,
		  (memoryTable[phyPage].vPage-mmapPtr->beginPage)*PageSize);
	ASSERT(mmapBytesToWrite==numBytesWritten);
      } else { // it's not mmaped
	DEBUG('p', "paging out: pid %i, phyPage %i, vpn %i\n",
	      memoryTable[phyPage].pid, phyPage, memoryTable[phyPage].vPage);
	numBytesWritten=memoryTable[phyPage].swapPtr->
	  WriteAt(machine->mainMemory+phyPage*PageSize, PageSize,
		  memoryTable[phyPage].vPage*PageSize);
	ASSERT(PageSize==numBytesWritten);
      }
    }
    delete memoryTable[phyPage].corrIptPtr;
    memoryTable[phyPage].valid=FALSE;
  }
}

//----------------------------------------------------------------------
// DoPageIn
//      Actually pages in a phyPage/vpn combo from the swapfile.
//----------------------------------------------------------------------

void DoPageIn(int vpn, int phyPage)
{
  MmapEntry *mmapPtr;
  int numBytesRead;
  int mmapBytesToRead;

  if((mmapPtr=GetMmap(vpn))){ // mmaped file
    DEBUG('p', "mmap paging in: pid %i, phyPage %i, vpn %i\n",
	  currentThread->pid, phyPage, vpn);
    if(vpn==mmapPtr->endPage)
      mmapBytesToRead=mmapPtr->lastPageLength;
    else
      mmapBytesToRead=PageSize;
    numBytesRead=
      mmapPtr->openFile->ReadAt(machine->mainMemory+phyPage*PageSize,
				mmapBytesToRead,
				(vpn-mmapPtr->beginPage)*PageSize);
  ASSERT(numBytesRead==mmapBytesToRead);
  } else { // not mmaped
    DEBUG('p', "paging in: pid %i, phyPage %i, vpn %i\n", currentThread->pid,
	  phyPage, vpn);
    numBytesRead=currentThread->space->swapPtr->ReadAt(machine->mainMemory+
							  phyPage*PageSize,
							  PageSize,
							  vpn*PageSize);
  ASSERT(PageSize==numBytesRead);
  }
}

//----------------------------------------------------------------------
// clockAlgorithm
//      Determine where a vpn should go in phymem, and therefore what
// should be paged out. This clock algorithm is a variant of the one 
// discussed in the lectures.
//----------------------------------------------------------------------

int clockAlgorithm(void)
{
	int phyPage;
 
	while(true)
	{
		if ((!memoryTable[clockPointer].valid)  //The entry is on is not valid
			//The entry has  been in memory too long without being referenced
			|| ((!memoryTable[clockPointer].dirty) && (memoryTable[clockPointer].clockCounter >= OLD_ENOUGH)) 
			//the position has been dirtied (changed), and  this entry has  been in memory too long without being referenced
			|| ((memoryTable[clockPointer].dirty) && (memoryTable[clockPointer].clockCounter >= OLD_ENOUGH + DIRTY_ALLOWANCE)))  

		{	
			//Found a page and break out of the while loop
			phyPage = clockPointer;
			break;
		}

		// Age the clock point so it can be evicted soon
		memoryTable[clockPointer].clockCounter++;
		//Increase the clock pointer by 1. The clock Pointer acts like an arm
		clockPointer = (clockPointer + 1) % NumPhysPages;
	}

	//Increase the clock pointer by 1. Hence the next pointed value is the oldest entrey
	clockPointer = (clockPointer + 1) % NumPhysPages;
	return phyPage;
}

//----------------------------------------------------------------------
// GetMmap
//      Return an MmapEntry structure corresponding to the vpn.  Returns
// 0 if does not exist.
//----------------------------------------------------------------------

MmapEntry *GetMmap(int vpn)
{
  MmapEntry *mmapPtr;

  mmapPtr=currentThread->space->mmapEntries;
  while(mmapPtr->next){
    mmapPtr=mmapPtr->next;
    if(vpn>=mmapPtr->beginPage && vpn<=mmapPtr->endPage)
      return mmapPtr;
  }
  return 0;
}

//----------------------------------------------------------------------
// PageOutMmapSpace
//      Pages out stuff being mmaped (or just between beginPage and
// endPage.
//----------------------------------------------------------------------

void PageOutMmapSpace(int beginPage, int endPage)
{
  int vpn;
  int phyPage;

  for(vpn=beginPage; vpn<=endPage; vpn++){
    if((phyPage=VpnToPhyPage(vpn))==-1)
      continue;
    DoPageOut(phyPage);
  }
}
