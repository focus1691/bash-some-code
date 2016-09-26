import java.io.IOException;
import java.util.ArrayList;

public class Database {

	private ArrayList<Table> tableList = new ArrayList<Table>();
	private enum TableInstructions { READ, WRITE, EXIT }; /* Enumerator for creating a table */
	private TableInstructions tableInstructions;
	private enum TableMenu { OPEN, PRINT, EXIT }; /* Enumerator for selecting a table */
	private TableMenu tableMenu;
	private TextFile textFile;
	private boolean read = false;
	private Display display;
	
	Database(TextFile textFile) {
		this.textFile = textFile; /* One copy of TextFile object is stored here */
	}
	
	void createTables() throws IOException { /* Menu for creating table */
		String instruction;
		display = new Display();
		boolean createTable = true;
		do {
			display.showTableInstructions(); /* Print instructions for creating tables */
			instruction = display.getInstruction(); /* Get the instruction from display class */
			try {
				tableInstructions = TableInstructions.valueOf(instruction.toUpperCase());
				switch (tableInstructions) {
				case READ: readTable(); break; /* Read table from text file */
				case WRITE: writeTable(); break; /* Enter a table manually */
				case EXIT: System.out.println("Exiting"); createTable = false; break;
				}
			} catch (IllegalArgumentException e) {
				System.err.println("Invalid choice: " + instruction); /* Invalid command */
			}
		} while (createTable == true);
	}
	
	void readTable() {
		String file;
		read = true;
		/* Create a new table with (read == true) and get table name from display class */
		Table table = new Table(display.getTableName(), display);
		file = display.getFileName(); /* Get text file to read from */
		System.out.println("Reading table from " + file);
		if (table.createColumns(textFile, file, read) == true) {
			/* If columns read successfully, read the records from file and return true to break user selection loop */
			table.readRecords(textFile, file); /* Read records if the file was successfully opened */
			tableList.add(table); /* Add this table to the the table ArrayList*/
			table.printTable();
		}
	}
	
	void writeTable() throws IOException { /* Create the table manually */
		read = false;
		/* Create a new table with (read == false) and get table name from display class */
		Table table = new Table(display.getTableName(), display);
		table.createColumns(null, null, read); /* Do not pass the textFile or any filename because we are writing */
		table.enterRecords(); /* Add records */
		tableList.add(table); /* Add this table to the the table ArrayList*/
		table.printTable();
		table.userChoice(textFile);
	}
	
	void openTable() throws IOException {
		int i;
		System.out.print("Enter the name of that table that you would like to select ");
		String tableName = display.selectTable(); /* User selects table to open */
		for (i = 0; i < tableList.size(); i++) {
			if (tableName.equals(tableList.get(i).tableName)) {
				System.out.println("Table " + tableName + " selected");
				tableList.get(i).userChoice(textFile); /* Open command menu if table selected exists */
				return;
			}
		}
		System.err.println("Table " + tableName + " not found"); /* Invalid table name */
	}
	
	void printTableNames() {
		int i, j = 1;
		for (i = 0; i < tableList.size(); i++, j++) {
			/* Prints all table names from table ArrayList */
			System.out.println("Table " + j + ": " + tableList.get(i).tableName);
		}
	}
	
	void selectTable() throws IOException { /* Menu for selecting table */
		String instruction;
		boolean exit = false;
		do {
			display.tableInstructions(); /* Print instructions for opening tables */
			instruction = display.selectTable(); /* Get instruction from display class */
			try {
				tableMenu = TableMenu.valueOf(instruction.toUpperCase());
				switch (tableMenu) {
				case OPEN: openTable(); break; /* Open the selected table's command menu */
				case PRINT: printTableNames(); break; /* Print all table names */
				case EXIT: System.out.println("Exiting program"); exit = true; break;
				}
			} catch (IllegalArgumentException e) {
				System.err.println("Invalid choice: " + instruction); /* Invalid command */
			}
		} while (exit == false);
	}
}