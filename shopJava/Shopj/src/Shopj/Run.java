package Shopj;

import java.io.File;
//imports scanner repository
import java.util.Scanner;

public class Run {
//main class used to run project
	public static void main(String[] args) {

		// calls the function and has it equal to Shop shop
		Shop shop = new Shop("src/Shopj/stock.csv");

		// create the scanner to take in user input
		Scanner scan = new Scanner(System.in);

		// prints out list of options
		System.out.println("Choose a Number");
		System.out.println("----------------");
		System.out.println("[1] Use ShoppingList CSV");
		System.out.println("[2] Live Mode");
		System.out.println("[X] Quit");

		// scans the inputed option into the terminal
		String choice = scan.next();

		// if the user chooses option 1 it calls the function that fulfills a
		// shoppinglist order from a csv
		if (choice.equals("1")) {

			// scans next line for the input csv
			System.out.println("Please enter the filepath to your Shopping List CSV");
			String filep = scan.next();
			// checks if the csv exists
			File f = new File(filep);
			if (f.exists() && !f.isDirectory()) {
				// calls the function and has it equal to Customer user
				Customer user = new Customer(filep);
				shop.processOrder(user);
			} else {
				// if file does not exists print error and return to the main menu
				System.out.println("File does not exist");
				main(args);
			}

		}
		// if the user chooses 2 it starts live mode
		else if (choice.equals("2")) {
			ScannerInput.scanUser(shop);
		}
		// if the user chooses X or x it closes the scanner and ends the program
		else if (choice.equals("X") || choice.equals("x")) {
			System.out.println("You have exited the program");
			scan.close();
			System.exit(0);
		}
		// if the user chooses anything else. it prints an error message . not
		// recognizing the input and calls the main method again
		else {
			System.out.println("Input not recognised please choose again");
			main(args);

		}
	}

}
