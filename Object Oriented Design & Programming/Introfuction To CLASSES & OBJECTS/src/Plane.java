import java.util.Arrays;
import java.util.*;
import java.util.Comparator;

/**
 * Created by ghost on 24/2/2016.
 */
public class Plane {
    private PlaneSeat[] seat;
    private int numEmptySeats = 0;


    public Plane()
    {
        int i = 0;
        
        seat = new PlaneSeat[12];
        for(i=0; i<12; i++)
        {
            seat[i] = new PlaneSeat(i+1);
        }
        numEmptySeats = 12;
    }

    private  PlaneSeat[] sortSeats()
    {
    	int j;
        boolean flag = true;   // set flag to true to begin first pass
        PlaneSeat temp;   //holding variable
        PlaneSeat[] seatTemp = null;
        
        //Copy from Seat
        seatTemp = new PlaneSeat[12];
        for(j=0; j<12; j++)
        {
        	seatTemp[j] = new PlaneSeat(j+1);
        	if(seat[j].isOccupied())
        		seatTemp[j].assign(seat[j].getCustomerID());
        }
        
        //Bubble Sort
        while ( flag )
        {
               flag= false;    //set flag to false awaiting a possible swap
               for( j=0;  j < seat.length - 1;  j++ )
               {
                      if ( seatTemp[j].getCustomerID() > seatTemp[j+1].getCustomerID() )   
                      {
                              temp = seatTemp[ j ];                //swap elements
                              seatTemp[ j ] = seatTemp[ j+1 ];
                              seatTemp[ j+1 ] = temp;
                              flag = true;              //shows a swap occurred  
                     } 
               } 
         } 
        
        return seatTemp;
    }

    public void showNumEmptySeats()
    {
        int count = 0;
        int i = 0;

        for(i=0; i<12; i++)
        {
            if(!seat[i].isOccupied())
            count++;
        }
        System.out.println("There are " + count +" empty seats.");
    }

    public void ShowEmptySeats()
    {
        int i = 0;
        System.out.println("The following seats are empty: ");

        for(i=0; i<12; i++)
        {
            if(!seat[i].isOccupied())
            System.out.println("SeatID " + (i+1));
        }
    }

    public void showAssignedSeats(boolean bySeatID)
    {
        int i = 0;
        PlaneSeat[] tempSeat;
        if (bySeatID)
            tempSeat = seat;
        else
            tempSeat = sortSeats();

        System.out.println("The seats assigment are as follow : ");
        for(i=0; i<12; i++)
        {
            if(tempSeat[i].isOccupied())
                System.out.println("SeatID : " + tempSeat[i].getSeatID() +" assigned to CustomerID " + tempSeat[i].getCustomerID());
        }
    }

    public void assignSeat(int seatId, int cust_id)
    {
    	if(!seat[seatId].isOccupied())
    	{	
    		this.seat[seatId].assign(cust_id);
    		System.out.println("Seat Assigned!");
    	}
    	else
    	{
    		System.out.println("Seat already assigned to a customer");
    	}
    }

    public  void unAssignSeat(int seatID)
    {
        this.seat[seatID].unAssign();
        System.out.println("Seat Unassigned!");
    }
}
