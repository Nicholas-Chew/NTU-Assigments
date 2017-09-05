package Closed_Hash;

import com.algo.car;
/**
 * Created by ghost on 29/9/2016.
 */
public class Close_Hash_Entry
{
    // Structure to hold the table data
    private String key;
    private car value;
    private Close_Hash_Entry next;

    public Close_Hash_Entry(car value)
    {
        this.key = value.getCarPlate();
        this.value = value;
        this.next = null;
    }

    public Close_Hash_Entry()
    {}

    public String getKey()
    {
        return key;
    }

    public void setKey(String  key){this.key = key;}

    public car getValue()
    {
         return value;
    }

    public void setValue(car value)
    {
        this.value = value;
    }

    public Close_Hash_Entry getNext()
    {
     return next;
    }

     public void setNext(Close_Hash_Entry next)
     {
      this.next = next;
     }

}
