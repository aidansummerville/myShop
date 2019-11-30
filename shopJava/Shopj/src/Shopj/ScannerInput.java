package Shopj;

import java.text.DecimalFormat;
import java.util.*;

public class ScannerInput {

	
	    // puts  floats to 2 decimal places
		private static DecimalFormat df = new DecimalFormat("0.00");	
	
	public static void scanUser(Shop s) {

		// calls arraylist n which stores inputed names
		ArrayList<String> n = new ArrayList<String>();
		// calls arraylist q which stores updates stock quantity's for those names
		ArrayList<String> q = new ArrayList<String>();
		// filepath to the stock csv
		String filepath = "src/Shopj/stock.csv";
		// gets the current cash in the shop
		String oldCash = String.valueOf(df.format(s.getCash()));

		// create the scanner to take in user input
		Scanner scan = new Scanner(System.in);

		// ask the user for what they want to buy and save as string
		System.out.println("What product do you want to buy?");
		String productName = scan.nextLine();
		// declares int found = 0 to be used as a counter
		int found = 0;

		// for loop that iterates through all the stock
		for (ProductStock productStock1 : s.getStock()) {

			// if the inputed name = a product name in stock continue
			if (productStock1.getProduct().getName().equals(productName)) {

				// increment found counter by 1
				found++;

				// add the inputed name to the n arraylist
				n.add(productName);
				// Ask how many of this product they want and save as a integer
				System.out.println("How many " + productName + " do you want?");
				int amount = scan.nextInt();

				// if the quantity they want is less than or = to what we have in stock continue
				if (amount <= productStock1.getQuantity()) {

					// int nq = gets the updated quantity in stock for this item
					int nQ = productStock1.getQuantity() - amount;
					// turn nq into a string called newq
					String newQ = String.valueOf(nQ);
					// append newQ the q arraylist for storing the updated quantity's in stock
					q.add(newQ);
					// new double cost = the product price * quantity requested
					double cost = productStock1.getProduct().getPrice() * amount;
					// find out how much money they have to pay you with and store it in the cash
					// variable
					System.out.println("The price for " + amount + " items 0f " + productName + " is €" + df.format(cost)
							+ " How much money do you have?");
					double cash = scan.nextDouble();
					// if they have enough money to buy the products there requesting continue
					if (cash >= cost) {
						// ask them weather they wish to confirm there purchase
						System.out.println("You have enough money to continue this purchase");
						System.out.println("Do you wish to proceed ?");
						System.out.println("Y/N");
						// variable nCash = the updated cash in shop
						double nCash = s.getCash() + cost;
						String updateCash = String.valueOf(df.format(nCash));
						String choose = scan.next();
						// if they choose to confirm with Y or y
						if (choose.equals("Y") || choose.equals("y")) {
							// print confirmation
							System.out.println("Your order has been confrimed please shop here again!");

							// calls shop class
							Shop shop = new Shop("src/Shopj/stock.csv");
							// calls shop.update function to update the stock.csv and passes the filepath,
							// the oldcash , the newcash the n arraylist and the q arraylist to the function
							shop.update(filepath, oldCash, updateCash, n, q);
						}
						// if the user chooses N or n prints a cancellation message
						else if (choose.equals("N") || choose.equals("n")) {
							System.out.println("Your order has been cancelled please shop here again !");

						}
						// if something else is entered it prints an input unrecognized message
						else {
							System.out.println("Sorry entry not recognised transaction cancelled");
						}
					}
					// if you do not have enough cash error message
					else {

						System.out.println("You have €" + df.format(cash) + " the total price of this trnsaction is €" + df.format(cost)
								+ " please remove items from your basket");
					}

				}
				// if you have chosen more of a product than there is in stock error message
				else {

					System.out.println("You have choosen " + amount + " of the product " + productName
							+ ". There is only " + productStock1.getQuantity()
							+ " of this product left in stock please reduce your order.");
				}
			}
			// closes scanner
			scan.close();
		}
		// if the product your looking for in not in the stock file error message
		if (found == 0) {
			System.out.println(productName + " is not currently in stock please choose another item");

		}

	}

}