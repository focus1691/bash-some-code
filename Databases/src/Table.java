import java.io.IOException;
import java.util.ArrayList;

public class Table {

	protected String tableName;
	private ArrayList<Record> recordList = new ArrayList<Record>(); /* This ArrayList contains all record objects */
	private int rowsInTable;
	private int line = 0; /* Current line position for reading text file (0 == first line) */
	private int ID = 100;
	private Columns columns;
	private Display display;
	/* Commands to manipulate the record list */
	private enum Choice { COLSIZE, ROWSIZE, GETCOL, SETCOL, GETROW, SETROW, ADDROW, DELROW, PRINT, SAVE, EXIT; };
	private Choice choice;
	
	Table(String tableName, Display display) {
		this.tableName = tableName;
		this.display = display;
	}
	
	boolean createColumns(TextFile textFile, String file, boolean read) {
		columns = new Columns(display);
		if (read == true) {
			try {
				rowsInTable = textFile.getNumberOfLines(file);
				if (textFile.readColumns(columns.columns, file) == true) line++; return true;
			} catch (IOException e) {
				System.err.println(e.getMessage()); // Print the error message if generated
			}
		} else {
			columns.enterColumns();
			return true;
		}
		return false;
	}
	
	void enterRecords() {
		boolean addRecord = true;
		String name = "record";
		while (addRecord == true) {
			display.getDecision(name);
			if (display.isValidDecision() == true) { /* Check if the decision is 'y' to create or 'n' to 'exit' */
				if (display.checkDecision() == true) { /* Create a new record if the decision is 'y' */
					Record record = new Record(display, columns.columns, columns.columns.size());
					ID++;
					record.createRecord(ID);
					recordList.add(record);
				} else { /* Exit the loop is the decision is 'n' */
					addRecord = false;
					break;
				}
			}
		}
	}
	
	void readRecords(TextFile textFile, String file) {
		while (line < rowsInTable) {
			try {
				ID++;
				Record record = new Record(display, columns.columns, columns.columns.size());
				/* Read record from current text file line */
				textFile.readRecord(ID, columns.columns.size(), record.record, line, file);
				recordList.add(record);
				line++; /* Increment the line to read the text file */
			} catch (IOException e) {
				System.out.println(e.getMessage());
			}
		}
	}
	
	void addRecord() { /* Add a new record */
		ID++;
		Record record = new Record(display, columns.columns, columns.columns.size());
		record.createRecord(ID);
		recordList.add(record);
		System.out.println("Record: " + ID + " added");
	}
	
	void deleteRecord() { /* Delete an existing record */
		int i;
		if (display.selectRecord(recordList.size(), recordList) == true) {
			for (i = 0; i < recordList.size(); i++) {
				if (String.valueOf(display.recordNumber).equals(recordList.get(i).record.get(0))) {
					recordList.remove(i);
					System.out.println("Record " + display.recordNumber + " deleted");
					break;
				}
			}
		}
	}
	
	void getRecord() {
		int i;
		if (display.selectRecord(recordList.size(), recordList) == true) {
			System.out.print("Record " + display.recordNumber + ":");
			for (i = 0; i < recordList.size(); i++) {
				if (String.valueOf(display.recordNumber).equals(recordList.get(i).record.get(0))) {
					recordList.get(i).print(); /* Display the chosen record */
					break;
				}
			}
		}
	}
	
	void setRecord() {
		int i;
		if (display.selectRecord(recordList.size(), recordList) == true) {
			for (i = 0; i < recordList.size(); i++) {
				if (String.valueOf(display.recordNumber).equals(recordList.get(i).record.get(0))) {
					System.out.println("Changing: Record " + display.recordNumber);
					recordList.get(i).changeRecord(); /* Change the selected record */
					break;
				}
			}
		}
	}

	void printTable() {
		int i;
		columns.printColumns(); /* Print all columns */
		int recordCount = recordList.size();
		for (i = 0; i < recordCount; i++) {
			recordList.get(i).print(); /* Loop through all record objects and execute their print methods */
		}
	}
	
	void saveTable(TextFile textFile) throws IOException {
		String extension = ".txt"; /* Extension to make selection a text file */
		/* Save the table to a text file */
		textFile.writeTable(columns.columns, recordList, display.getFileName() + extension);
	}
	
	void getCol() {
		boolean set = false;
		columns.getColumn(columns.columns.size(), set); /* Call getColumn() with (set == false) to print a selected column */
	}
	
	void setCol() {
		boolean set = true;
		columns.getColumn(columns.columns.size(), set); /* Call getColumn() with (set == true) to change a column name */
	}

	void userChoice(TextFile textFile) throws IOException {
		String instruction;
		boolean exit = false;
		do {
			display.showCommandInstructions();
			instruction = display.getInstruction();
			try {
				choice = Choice.valueOf(instruction.toUpperCase());
				switch(choice) {
				case COLSIZE: columns.printColumnSize(); break; /* Column size */
				case ROWSIZE: System.out.println("There are " + recordList.size() + " records"); break; /* Row count */
				case GETCOL: getCol(); break; /* Get a column name */
				case SETCOL: setCol(); break; /* Change a column name */
				case GETROW: getRecord(); break; /* Print a record */
				case SETROW: setRecord(); break; /* Change a record */
				case ADDROW: addRecord(); break; /* Add a new record */
				case DELROW: deleteRecord(); break; /* Delete an existing record */
				case PRINT: printTable(); break; /* Print all records */
				case SAVE: saveTable(textFile); break; /* Save the table to a new text file */
				case EXIT: System.out.println("Exiting"); exit = true; break; /* Exit loop */
				}
			} catch (IllegalArgumentException e) {
				/* Must be a valid value for enumerator Choice */
				System.err.println("Invalid choice: " + instruction);
			}
		} while (exit == false);
	}
}
