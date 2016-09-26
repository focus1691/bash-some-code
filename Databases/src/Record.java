import java.util.ArrayList;

public class Record {

	protected ArrayList<String> record = new ArrayList<String>(); /* Values for this record are stored here */
	protected ArrayList<String> fields = new ArrayList<String>();
	private Display display;
	private int fieldCount;

	Record(Display display, ArrayList<String> fields, int fieldCount) {
		this.display = display;
		this.fields = fields; /* This record object receives all field values */
		this.fieldCount = fieldCount;
	}
	
	void createRecord(int ID) { /* Loop until the number of fields is reached */
		int i;
		record.add(String.valueOf(ID));
		for (i = 1; i < fieldCount; i++) { /* Start at 1 to ignore the ID column */
			System.out.println("Enter a value for " + fields.get(i));
			record.add(display.setRecordValue());
		}
	}

	void print() {
		int i;
		for (i = 0; i < fieldCount; i++) {
			System.out.printf("%10s", record.get(i)); /* Print the values in this record object */
		}
		System.out.println();
	}
	
	void changeRecord() {
		int i;
		for (i = 1; i < fieldCount; i++) { /* Start at 1 to ignore the ID column */
			System.out.println("Enter a new value for " + fields.get(i));
			/* Replaces values in this record with user input */
			record.set(i, display.selection = display.instructInput.nextLine());
		}
	}
}