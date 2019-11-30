package Shopj;

public class ProductStock {
	private Product product;
	private int quantity;

	public ProductStock(Product product, int quantity) {
		super();
		this.product = product;
		this.quantity = quantity;
	}

	// getter for product
	public Product getProduct() {
		return product;
	}

//getter for quantity
	public int getQuantity() {
		return quantity;
	}

	@Override
	public String toString() {
		return "ProductStock [product=" + product + ", quantity=" + quantity + "]";
	}

}
