import java.util.ArrayList;

public class Columns {

	protected ArrayList<String> columns = new ArrayList<String>();
	Display display;

	private boolean addField = true;
	private String field;
	private String selectedColumn;
	
	Columns(Display display) {
		this.display = display;
	}
	
	void enterColumns() {
		String name = "column";
		columns.add("ID");
		while (addField == true) {
			display.getDecision(name);
			if (display.isValidDecision() == true) { /* Check if the decision is 'y' to create column or 'n' to 'exit' */
				if (display.checkDecision() == true) { /* Create a column if the decision is 'y' */
					System.out.println("Enter a new field name");
					field = display.input.nextLine();
					columns.add(field);
				} else { /* Exit the loop if the decision is 'n' */
					addField = false;
					break;
				}
			}
		}
	}
	
	void getColumn(int size, boolean set) {
		int i;
		String name;
		System.out.println("Enter the column name");
		name = display.input.nextLine();
		for (i = 0; i < size; i++) {
			if (columns.get(i).equals(name)) { /* Check if the entered column matches any of the existing ones */
				selectedColumn = columns.get(i);
				System.out.println(selectedColumn); /* Print selected column if a match is found */
				if (set == true) {
					setColumn(i); /* Call 'setColumn()' if user has chosen to change the column (set == true) */
				}
				return;
			}
		}
		System.err.println("Invalid column name\n");
	}
	
	void setColumn(int colNum) {
		System.out.print("Enter a new column name ");
		columns.set(colNum, display.changeColumnName()); /* Change the column name with user input from display method */
		System.out.print("\nColumn " + selectedColumn + " renamed to "); /* Old column name */
		selectedColumn = columns.get(colNum);
		System.out.println(selectedColumn); /* New column name */
	}
	
	void printColumns() {
		for (String arr : columns) { 
			System.out.printf("%10s", arr); /* Print all columns */
		}
		System.out.println();
	}
	
	int getColumnSize() {
		return columns.size(); /* returns number of columns */
	}
	
	void printColumnSize() {
		System.out.println("There are " + getColumnSize() + " columns"); /* Call 'getColumnSize()' to get the column count */
	}
}