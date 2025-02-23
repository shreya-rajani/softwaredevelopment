import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.ArrayList;

/**
 * This is the Driver class which takes in the argument from the console and
 * then separates the flags and the name and it calls the other functions
 * 
 * @author shreyarajani
 * 
 */
public class Driver {

	/**
	 * Calls all the methods and checks for -d and -i flags
	 * 
	 * @param args
	 *            - input from the console by the user
	 */
	public static void main(String[] args) {
		ArgumentParser argumentParser = new ArgumentParser(args);
		ParseQuery parseQuery;

		// checks if it it has -d and processes the path and adds to
		// InvertedIndex
		if (argumentParser.hasFlag("-d")) {
			String dir = argumentParser.getValue("-d");
			Path path = Paths.get(dir);
			InvertedIndex ii = new  InvertedIndex();
			DirectoryTraverser dirTraveralOb = new DirectoryTraverser(ii);
			dirTraveralOb.traverse(path);

			// Checks of -i and passes the arguments after -i to printTMap to
			// create a text file with that name or else with a default name
			// invertedindex.txt
			if (argumentParser.hasFlag("-i")) {
				ii.printIndex("invertedindex.txt");
			}
			if (argumentParser.hasFlag("-i")) {
				if (argumentParser.hasValue("-i")) {
					String outfile = argumentParser.getValue("-i");
					ii.printIndex(outfile);
				} else {
					ii.printIndex("invertedindex.txt");
				}
			}

			// Takes -q as the query file that is followed by -q
			parseQuery = new ParseQuery(ii);
			if (argumentParser.hasFlag("-q")) {
				if (argumentParser.hasValue("-q")
						&& argumentParser.getValue("-q") != null) {
					String queryFile = argumentParser.getValue("-q");
					Path inpath = Paths.get(queryFile);
					parseQuery.parseQuery(inpath);
				} else {
					System.out.println("No query File Submitted!");
				}
			}

			// the file name followed by -r would store the search result in it.
			if (argumentParser.hasFlag("-r")) {
				if (argumentParser.hasValue("-r")) {
					String resultFile = argumentParser.getValue("-r");
					parseQuery.printSearchIndex(resultFile);
				} else {
					parseQuery.printSearchIndex("searchresults.txt");
				}
			}

		} else {
			System.out.println("Invalid input, please give a directory");
			System.out
					.println("Usage: -d <directory> -i <output filename> -q <query file> -r <result File>");
		}
	}
}