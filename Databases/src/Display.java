import java.util.ArrayList;
import java.util.Scanner;

public class Display {

	protected Scanner input = new Scanner(System.in);
	protected Scanner instructInput = new Scanner(System.in);
	protected Scanner colInput = new Scanner(System.in);
	protected Scanner fileInput = new Scanner(System.in);
	protected String selection;
	protected String decision;
	protected String columnName;
	protected int recordNumber;
	
	String getTableName() {
		System.out.print("This table will be called: ");
		return input.nextLine();
	}
	
	String selectTable() {
		return input.nextLine();
	}
	
	void tableInstructions() {
		System.out.print("Enter 'open' to select a table\t\t");
		System.out.print("Enter 'print' to print the table names");
		System.out.println("\t\tEnter 'exit' to exit the program");
	}
	
	String getFileName() {
		System.out.print("Enter a file name: ");
		return fileInput.nextLine();
	}
	
	void getDecision(String name) {
		System.out.print("Enter 'y' to add a new " + name + " or 'n' to stop: ");
		decision = input.nextLine();
	}
	
	String setRecordValue() {
		return input.nextLine();
	}
	
	boolean isValidDecision() {
		System.out.println(decision);
		if (decision.equals("y") || decision.equals("n")) { /* Check if decision is valid: 'y' or 'n' */
			return true;
		} else {
			System.err.println("Invalid selection\n");
			resetDecision(); /* Reset the input string */
			return false; /* Restart the loop */
		}
	}
	
	boolean checkDecision() {
		switch(decision) {
		case "y": return true; /* Decision was yes */
		case "n": return false; /* Decision was no, so exit loop */
		default: return false; /* Something went wrong so exit */
		}
	}
	
	void resetDecision() {
		decision = "";
	}

	void showCommandInstructions() { /* Print valid commands for selecting to read/write a table */
		System.out.print("Enter 'colsize' to get the column size.\t\t");
		System.out.print("Enter 'rowsize' to get the row size.");
		System.out.println("\t\tEnter 'getcol' to print a column");
		System.out.print("Enter 'setcol' to change a column\t\t");
		System.out.print("Enter 'getrow' to print a record");
		System.out.println("\t\tEnter 'setrow' to change a record");
		System.out.print("Enter 'addrow' to add a new record\t\t");
		System.out.print("Enter 'delrow' to delete a record");
		System.out.println("\t\tEnter 'print' to print the table");
		System.out.print("Enter 'save' to save the table to file\t\t");
		System.out.println("Enter 'exit' to quit the program");
	}
	
	void showTableInstructions() { /* Print valid commands for selecting to read/write a table */
		System.out.println("Enter 'read' to create a table from a text file.");
		System.out.println("Enter 'write' to create a table manually.");
		System.out.println("Enter 'exit' to stop creating tables.");
	}

	String getInstruction() {
		return instructInput.nextLine();
	}
	
	String changeColumnName() {
		return columnName = colInput.nextLine();
	}
	
	boolean selectRecord(int size, ArrayList<Record> record) {
		int i;
		if (size == 0) {
			System.err.println("No records available"); /* No available records */
			return false;
		} else {
			System.out.println("Enter the record's ID to select it");
			recordNumber = input.nextInt(); /* Record number is used to select it */
			for (i = 0; i < size; i++) {
				if (String.valueOf(recordNumber).equals(record.get(i).record.get(0))) return true;
			}
		}
		System.err.println("Invalid record number"); /* Invalid selection */
		return false;
	}
	
	boolean changeRecord() {
		boolean validDecision = false;
		System.out.println("\nWould you like to change this record? Type 'y' for yes and 'n' for no");
		decision = input.nextLine();
		while (validDecision == false) {
			if (isValidDecision() == true) validDecision = true; break;
		}
		if (checkDecision() == true) return true;
		else return false;
	}
}
