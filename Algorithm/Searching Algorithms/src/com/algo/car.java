package com.algo;

/**
 * Created by ghost on 29/9/2016.
 */
public class car {
    private String carPlate;
    private String carModel;
    private Boolean rented = false;

    public car(String carPlate, String carModel)
    {
        this.carPlate = carPlate;
        this.carModel = carModel;
    }

    public car()
    {}

    public void setCarPlate(String carPlate)
    {
        this.carPlate = carPlate;
    }

    public void setCarModel(String carModel)
    {
        this.carPlate = carModel;
    }

    public String getCarPlate()
    {
        return carPlate;
    }

    public String getCarModel()
    {
        return carModel;
    }

}
