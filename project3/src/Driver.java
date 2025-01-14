import java.nio.file.Path;
import java.nio.file.Paths;

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

		if (argumentParser.hasFlag("-t")) {
			int threadCount;
			try {
				threadCount = Integer.parseInt(argumentParser.getValue("-t"));
			} catch (NumberFormatException e) {
				threadCount = 5;
			}

			MultithreadedInvertedIndex index = new MultithreadedInvertedIndex();
			if (threadCount > 0) {
				WorkQueue workers = new WorkQueue(threadCount);
				MultithreadedIndexBuilder traverser = new MultithreadedIndexBuilder(
						index, workers);

				if (argumentParser.hasFlag("-d")) {
					String dir = argumentParser.getValue("-d");
					Path path = Paths.get(dir);
					traverser.traverse(path);
					//traverser.finish();
					traverser.shutdown();

					if (!argumentParser.hasFlag("-q")) {
						if (!argumentParser.hasFlag("-i")) {
							index.printIndex("invertedindex.txt");
						}
					}
				}

				if (argumentParser.hasFlag("-q")) {
					MultiThreadedIndexSearcher searcher = new MultiThreadedIndexSearcher(
							index, workers);
					String queryFile = argumentParser.getValue("-q");
					Path inpath = Paths.get(queryFile);
					searcher.parseQuery(inpath);
					searcher.finish();
					if (argumentParser.hasFlag("-r")) {
						if (argumentParser.getValue("-r") != null) {
							String resultFile = argumentParser.getValue("-r");
							searcher.printSearchIndex(resultFile);
						}
					}

					if (argumentParser.hasFlag("-r")) {
						if (argumentParser.getValue("-r") == null) {
							String resultFile = "searchresults.txt";
							searcher.printSearchIndex(resultFile);
						}
					}
					searcher.shutdown();
					workers.shutdown();
				}

				if (argumentParser.hasFlag("-i")) {
					if ((argumentParser.getValue("-i")) != null) {
						String outfile = argumentParser.getValue("-i");
						index.printIndex(outfile);
					}
				}
			}

		} else {

			InvertedIndex ii = new InvertedIndex();
			DirectoryTraverser dirTraveralOb = new DirectoryTraverser(ii);

			if (argumentParser.hasFlag("-d")) {
				String dir = argumentParser.getValue("-d");
				Path path = Paths.get(dir);
				dirTraveralOb.traverse(path);
				IndexSearcher parseQuery;

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
				parseQuery = new IndexSearcher(ii);
				if (argumentParser.hasFlag("-q")) {
					if (argumentParser.hasValue("-q")) {
						if (argumentParser.getValue("-q") != null) {
							String queryFile = argumentParser.getValue("-q");
							Path inpath = Paths.get(queryFile);
							parseQuery.parseQuery(inpath);
						} else {
							System.out.println("No query File Submitted!");
						}
					}
				}

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
}