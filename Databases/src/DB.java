import java.io.IOException;

public class DB {

	private TextFile textFile;
	private Database database;
	
	public static void main(String[] args) throws IOException {
		DB newDB = new DB();
		newDB.setup();
	}
	
	void setup() throws IOException {
		textFile = new TextFile();
		database = new Database(textFile);
		database.createTables();
		database.selectTable();
	}
}