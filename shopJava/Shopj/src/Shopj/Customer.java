package Shopj;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Customer {

	private String uname;
	private double budget;
	ArrayList<ProductStock> shoppingList;

	public Customer(String fileName) {

		// declares the private arraylist called shoppinglist that will store the input
		// shoppinglist csv from the rest of the csv
		shoppingList = new ArrayList<ProductStock>();
		// declares list string to be used to read the csv line by line
		List<String> lines = Collections.emptyList();
		try {
			// lines reads all the lines in the input shopping list csv
			lines = Files.readAllLines(Paths.get(fileName), StandardCharsets.UTF_8);

			// splits the lines up the commas
			String[] firstLine = lines.get(0).split(",");
			// the shoppers budget is the first locatiion on the first line
			budget = Double.parseDouble(firstLine[0]);
			// the shoppers name is on the second location on the firsts line
			uname = firstLine[1];

			// removes the first line
			lines.remove(0);
			// for loop iterates through each of the remaining lines in the shopping list
			for (String line : lines) {
				// splits the lines by commas
				String[] arr = line.split(",");
				// product name is in the first location on each line
				String name = arr[0];
				// product quantity is in the second location on each line
				int quantity = Integer.parseInt(arr[1].trim());
				// adds name to product
				Product p = new Product(name, 0);
				// adds product and quantity to product stock
				ProductStock s = new ProductStock(p, quantity);
				// adds them all to the shoppinglist arraylist
				shoppingList.add(s);

			}
		}

		catch (IOException e) {

			// do something
			e.printStackTrace();
		}
	}

	public String getUname() {
		return uname;
	}

	public double getBudget() {
		return budget;
	}

	public ArrayList<ProductStock> getShoppingList() {
		return shoppingList;
	}

	@Override
	public String toString() {
		String ret = "Customer [uname=" + uname + ", budget=" + budget + ", shoppingList=\n";
		for (ProductStock productStock : shoppingList) {
			ret += productStock.getProduct().getName() + " Quantity: " + productStock.getQuantity() + "\n";
		}
		return ret + "}";
	}

	public void setShoppingList(ArrayList<ProductStock> shoppingList) {
		this.shoppingList = shoppingList;
	}

}
