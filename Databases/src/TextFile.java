import java.io.FileWriter;
import java.io.IOException;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.PrintWriter;
import java.util.ArrayList;

public class TextFile {

	private String delimiterRead = "\\|\\|##"; /* The delimiter to separate column and record names with escape sequence */
	private String delimiterWrite = "||##"; /* The delimiter to separate column and record names when writing */

	boolean readColumns(ArrayList<String> array, String file) throws IOException {
		
		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		String line;
		int linePos = 0;
		String ID = "ID";
		
		array.add(ID);
		try {
			if ((line = br.readLine()) != null) { /* Store the line read in the string 'line' */
				/* Split the string using the delimiter and read the values one by one */
				for (String arr : line.split(delimiterRead)) {
					array.add(arr); /* Add the column names to the passed column ArrayList */
				}
				br.close();
				return true;
			}
		} catch (IOException e) {
			System.err.println(e.getMessage());
		}
		br.close();
		return false; /* Line one unsuccessfully read */
	}

	void readRecord(int ID, int colSize, ArrayList<String> record, int readLine, String file) throws IOException {

		FileReader fr = new FileReader(file);
		BufferedReader br = new BufferedReader(fr);
		String line;
		int linePos = 0;
		int i;
		
		record.add(String.valueOf(ID)); /* Add the id value to the first column of this record */
		while ((line = br.readLine()) != null) {
			String[] ar = line.split(delimiterRead);
			if (linePos == readLine) {
				for (i = 1; i < colSize; i++) { /* Start at 1 to skip the ID column */
					for (String arr : ar) {
						record.add(arr);
						i++;
					}
					record.add(""); /* Make the record value blank if no value is supplied for a given column name */
				}
				break; /* Stop reading when the current line is read from the text file into the record object */
			}
			linePos++; /* Increment the line position until the text file gets to the correct line chosen to read from */
		}
		br.close();
	}
	
	void writeTable(ArrayList<String> columns, ArrayList<Record> record, String file) throws IOException {
		int i, j;

		try {
			FileWriter fw = new FileWriter(file);
			PrintWriter pw = new PrintWriter(fw);
		
			for (i = 0; i < columns.size(); i++) { /* Loop through all the columns */
				if (i == columns.size() - 1) {
					pw.print(columns.get(i)); /* Insert column name without delimiter if end of line is reached */
				} else {
					/* Insert column name with delimiter if end of line is not reached */
					pw.print(columns.get(i) + delimiterWrite);
				}
			}
			pw.println(); /* Insert a line after the columns that were entered */
			for (i = 0; i < record.size(); i++) { /* Loop through all the record objects */
				for (j = 0; j < columns.size(); j++) { /* Inner loop to select a value for each of the available columns */
					if (j == (columns.size() - 1)) {
						/* Insert record value without delimiter if end of line is reached */
						pw.print(record.get(i).record.get(j));
					} else {
						/* Insert record value with delimiter if end of line is not reached */
						pw.print(record.get(i).record.get(j) + delimiterWrite);
					}
				}
				pw.println(); /* Insert a new line to separate each record */
			}
			System.out.println("Table saved to " + file);
			pw.close();
		} catch (IOException e) {
			System.out.println(e.getMessage());
		}
	}
	
	int getNumberOfLines(String file) throws IOException { /* Get number of lines from text file (colLen == ((n)-(n-1))
	 	(rowLen == (n-1))*/
		FileReader fr = new FileReader(file);
		BufferedReader bf = new BufferedReader(fr);
	
		String aLine;
		int numberOfLines = 0;
		
		while ((aLine = bf.readLine()) != null) { /* Read until the text file is empty */
			numberOfLines++; /* Increment line count for every line read */
		}
		bf.close();
		return numberOfLines;
	}
}