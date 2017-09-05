package Open_Hash;

import com.algo.car;

/**
 * Created by ghost on 29/9/2016.
 */
public class Open_Hash_Entry {

    // Structure to hold the table data
    private String key;
    private car value;


    public Open_Hash_Entry(car value) {
        this.key = value.getCarPlate();
        this.value = value;
    }

    public Open_Hash_Entry()
    {}

    public String getKey() {
        return key;
    }

    public void setKey(String key){this.key = key;}

    public car getValue() {
        return value;
    }

    public void setValue(car value)
    {
        this.value = value;
    }

}
