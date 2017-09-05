import java.util.Scanner;
/**
 * Created by ghost on 24/2/2016.
 */
public class App {

    public static void  main(String[] Arg)
    {
        int choice;
        int seatID, customerID;
        Plane plane = new Plane();
        System.out.println("(1) Show the number of empty seats");
        System.out.println("(2) Show the list of empty seats");
        System.out.println("(3) Show the list of customers together with their seat numbers in the order of the seat numbers");
        System.out.println("(4) Show the list of customers together with their seat numbers in the order of the customer ID");
        System.out.println("(5) Assign a customer to a seat");
        System.out.println("(6) Remove a seat assigment");
        System.out.println("(7) Quit");



        while(true) {
            System.out.print("Enter the number of your choice :");

            Scanner sc  = new Scanner(System.in);
            choice = sc.nextInt();

            switch (choice) {
                case 1:
                        plane.showNumEmptySeats();
                        System.out.println("");
                    break;
                case 2:
                        plane.ShowEmptySeats();
                        System.out.println("");
                    break;
                case 3:
                        plane.showAssignedSeats(true);
                        System.out.println("");
                        break;
                case 4:
                         plane.showAssignedSeats(false);
                    break;
                case 5:
                	System.out.println("Assigning Seat ...");
                    System.out.print("	Please enter SeatID :");
                    seatID = sc.nextInt();
                    System.out.print("	Please enter Customer ID :");
                    customerID = sc.nextInt();
                    
                    plane.assignSeat(seatID-1,customerID);
                    System.out.println("");
                    
                    break;
                case 6:
                    System.out.print("Enter SeatID to unassign customer from:");
                    seatID = sc.nextInt();

                    plane.unAssignSeat(seatID -1);
                    break;
                case 7:
                    return;
            }
        }
    }
}
