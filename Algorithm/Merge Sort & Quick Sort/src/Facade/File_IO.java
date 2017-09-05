package Facade;

import java.beans.XMLEncoder;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;

public class File_IO {
	
	public static void writeToXML(String file_Name,Object obj) throws Exception
	{
		try
		{
			//Make Folder Data if not exists
			new File(System.getProperty("user.dir") +"/Data").mkdirs();

			//Make File if not exists
			File tempFile = new File(System.getProperty("user.dir") +"/Data/"+file_Name+".xml");
			if(!tempFile.exists()) {
				tempFile.createNewFile();
			} 
			
			//XML Encoder
			XMLEncoder encoder = new XMLEncoder(new BufferedOutputStream(
		                   			new FileOutputStream(System.getProperty("user.dir") +"/Data/"+file_Name+".xml")));
								
			encoder.writeObject(obj);
			encoder.close(); 
		}
		catch(Exception e)
		{
			throw new Exception(e+" File : "+file_Name);
		}
	}
	
	

}
