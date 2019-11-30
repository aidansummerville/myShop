package Shopj;

import java.io.*;

import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Scanner;

public class Shop {
	
	// puts  floats to 2 decimal places
	private static DecimalFormat df = new DecimalFormat("0.00");

	// declares private variable cash that will store the stock cash from the first
	// line of the csv
	private double cash;
	// declares the private arraylist called stock that will store the stock from
	// the rest of the csv
	private ArrayList<ProductStock> stock;

	// calls function shop that takes a string that represents the filename for the
	// stock.csv
	public Shop(String fileName) {
		stock = new ArrayList<>();
		// declares lines which will be used to read the csv line by line
		List<String> lines = Collections.emptyList();
		try {
			// lines reads all the lines in the stock.csv
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);

			// cash = line one of the csv
			cash = Double.parseDouble(lines.get(0));

			// i am removing at index zero as it is the only line treated differently
			lines.remove(0);
			// for loop for all the lines in lines
			for (String line : lines) {
				// array string is split up by commas in the lines
				String[] arr = line.split(",");
				// product name is at point 0 in the string
				String name = arr[0];
				// price is the second position
				double price = Double.parseDouble(arr[1]);
				// quantity is in the third position
				int quantity = Integer.parseInt(arr[2].trim());
				// adds the name and the price to product
				Product p = new Product(name, price);
				// then adds the product and the quantity to product stock
				ProductStock s = new ProductStock(p, quantity);
				// appends to the stock arraylist
				stock.add(s);

			}
		}

		catch (IOException e) {

			// do something
			e.printStackTrace();
		}
	}

	// getter for cash
	public double getCash() {
		return cash;
	}

	public ArrayList<ProductStock> getStock() {
		return stock;
	}

	@Override
	public String toString() {
		return "Shop [cash= " + cash + ", stock=" + stock + "]";

	}

	// takes in a product name
	private double findPrice(String name) {
		// for loop that iterates through each product in stock
		for (ProductStock productStock : stock) {
			Product p = productStock.getProduct();
			// if the input string name == a product name in stock it returns the price
			if (p.getName().equals(name)) {
				return p.getPrice();
			}
		}
		return -1;
	}

	private static Scanner x;

	// updates the stock csv with new quantity's
	// function takes a string for the file location the stock csv, takes the old
	// stock cash, the new stock cash , and an arraylist of product names and an
	// arraylist of new product stock quantity's
	public  void update(String filepath, String oldCash, String updateCash, ArrayList<String> name,
			ArrayList<String> newQ) {
		// for loop that loops through the csv going through each product name in it
		for (int i = 0; i < name.size(); i++) {
			// creates a string called temp.csv
			String tempFile = "temp.csv";
			// declares the stock.csv as oldfile using filepath
			File oldFile = new File(filepath);
			// creates the temp.csv as a file
			File newFile = new File(tempFile);
			// splits the csv by commas and names each part
			String First = "";
			String Second = "";
			String Third = "";
			try {
				// opens the temp.csv file to write to
				FileWriter fw = new FileWriter(tempFile, true);
				BufferedWriter bw = new BufferedWriter(fw);
				PrintWriter pw = new PrintWriter(bw);
				// scans the oldfile and uses the newline character as the delimiter
				x = new Scanner(new File(filepath));
				x.useDelimiter("[,\n]");

				// prints the update cash to the first line
				pw.println(updateCash);
				// goes to next line
				x.nextLine();
				// while there is a next line loop through the stock.csv
				while (x.hasNext()) {
					// first = the name section of the csv
					First = x.next();
					// second = the price section f the csv
					Second = x.next();
					// third - the quantity section of the csv
					Third = x.next();
					// if the first a = the name in the arraylist n in this loop through the csv
					if (First.equals(name.get(i))) {
						// print the name plus the same price + the updated quantity
						pw.println(name.get(i) + "," + Second + "," + newQ.get(i));

					}
					// if the productname and doesnt match the first variable print the old line to
					// the temp.csv
					else {
						pw.println((First + "," + Second + "," + Third));

					}

				}
				// close the stock.csv and the temp.csv
				x.close();
				pw.flush();
				pw.close();
				// delete the stock.csv
				oldFile.delete();
				File dump = new File(filepath);
				// rename the temp.csv file to stock.csv and its path
				newFile.renameTo(dump);

			} catch (Exception e) {
				// TODO: handle exception
			}

		}

	}

	// function that compares input shoppingList verses product stock
	public void processOrder(Customer c) {
		// prints customer name and budget
		System.out.println("CUSTOMER NAME: " + c.getUname() + "\n" + "CUSTOMER BUDGET: " + df.format(c.getBudget()) + "\n"
				+ "-------------------------------");
		// declares a double to be used to calculate total spend
		double a = 0.00;
		// calls arraylist n which stores inputed names
		ArrayList<String> n = new ArrayList<String>();
		// calls arraylist q which stores updates stock quantity's for those names
		ArrayList<String> q = new ArrayList<String>();
		// for loop that iterates through all the customers shopping list
		for (ProductStock productStock : c.shoppingList) {

			// for loop that iterates through all the stock
			for (ProductStock productStock1 : stock) {
				// shoppinglist product name = the product name in stock continue
				if (productStock.getProduct().getName().equals(productStock1.getProduct().getName())) {
					// if the quantity of the product that is wanted is less than or = to what is in
					// stock continue
					if (productStock.getQuantity() - productStock1.getQuantity() <= 0) {
						// prints the product name
						System.out.println("PRODUCT NAME: " + productStock.getProduct().getName());

						Product p = productStock1.getProduct();
						// gets product quantity from shopping list
						int quantity = productStock.getQuantity();
						// gets product price
						double price = findPrice(p.getName());
						// makes total cost of product by multiplying price * quantity
						double cost = price * quantity;
						// prints out product name, user name , price and cost
						System.out.println(c.getUname() + " Orders " + quantity + " of Above Product " + "\n"
								+ "PRODUCT PRICE: " + df.format(price)+ "\n" + "The cost to " + c.getUname() + " will be " + df.format(cost)
								+ "\n" + "----------------------------");
						// gets the updated quantity for the current item in the stock
						int t = productStock1.getQuantity() - productStock.getQuantity();
						// turns it into a string
						String k = String.valueOf(t);
						// adds the product name to the n arraylist
						n.add(p.getName());
						// add the updated quantity to the q arraylist
						q.add(k);
						// adds cost to a to calculate total spend
						a = a + cost;

					}
					// error message for ordering more of an item than is in stock
					else {
						System.out.println("You have ordered " + productStock.getProduct().getName() + " of "
								+ productStock.getProduct().getName() + " , only "
								+ productStock1.getProduct().getName()
								+ " of this product left in stock please remove items from your shoppinglist" + "\n"
								+ "-------------------------");
					}

				}
			}
		}
		// prints total cost
		System.out.println("TOTAL: €" + df.format(a) + "\n" + "---------------------------");

		// declares newcash to for use in total spend
		double newCash;
		// declares change variable calculates how much customer spent
		double change = c.getBudget() - a;
		// if spend is less than budget continue
		if (change >= 0) {

			// newcash = shop cash + total spend
			newCash = cash + a;

			// print change and new shop cash
			System.out.println(
					"CHANGE: €" + df.format(change) + "\n" + "SHOPCASH: €" + df.format(newCash)+ "\n" + "---------------------------");

			// filepath to the stock csv
			String filepath = "src/Shopj/stock.csv";

			// gets the current cash in the shop and turns it into a string
			String oldCash = String.valueOf(df.format(cash));
			// gets the updated cash in the shop and turns it into a string
			String updateCash = String.valueOf(df.format(newCash));

			// calls shop.update function to update the stock.csv and passes the filepath,
			// the oldcash , the newcash the n arraylist and the q arraylist to the function
			update(filepath, oldCash, updateCash, n, q);

		}
	}

}
