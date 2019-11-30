package Shopj;

//declares class
public class Product {
	// declares variables name + price
	private String name;
	private double price;

	// declares Product
	public Product(String name, double price) {
		super();
		this.name = name;
		this.price = price;
	}

	// setter for price
	public void setPrice(double price) {
		this.price = price;
	}

	// getter for name
	public String getName() {
		return name;
	}

	// getter for price
	public double getPrice() {
		return price;
	}

	@Override
	public String toString() {
		return "Product [name=" + name + ", price=" + price + "]";
	}

}
