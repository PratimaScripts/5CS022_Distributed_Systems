package heraldcollege.edu.np;

import java.io.IOException;
import java.util.Arrays;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.spark.SparkConf;
import org.apache.spark.api.java.JavaPairRDD;
import org.apache.spark.api.java.JavaRDD;
import org.apache.spark.api.java.JavaSparkContext;
import scala.Tuple2;

public class LetterCount {
    
    public static void main(String[] args) {
        SparkConf sparkConf = new SparkConf();
        sparkConf.setAppName("Spark LetterCount example using Java");
        sparkConf.setMaster("local");
        
        JavaSparkContext sparkContext = new JavaSparkContext(sparkConf);
        
        JavaRDD<String> textFile = sparkContext.textFile("input.txt");
        
        JavaRDD<String> letters = textFile.flatMap(l -> Arrays.asList(l.split("")).iterator());
        
        JavaPairRDD<String, Integer> pairs = letters.mapToPair(l -> new Tuple2<String, Integer>(l, 1));
        
        JavaPairRDD<String, Integer> counts = pairs.reduceByKey((x, y) -> x + y);
        
        JavaPairRDD<String, Integer> sortedCounts = counts.sortByKey();
        
        String outputPath = "output"; 
        try {
            FileSystem.get(sparkContext.hadoopConfiguration()).delete(new Path(outputPath), true);
        } catch (IOException e) {
            e.printStackTrace();
        }

        try {
        	sortedCounts.saveAsTextFile(outputPath);
        } catch (Exception e) {
            e.printStackTrace();
        }
        	 
        System.out.println("Letter Counts:");
        
        for (Tuple2<String, Integer> tuple : sortedCounts.collect()) {
            System.out.println(tuple._1() + ": " + tuple._2());
        }
        
        sparkContext.stop();
        sparkContext.close();
    }
}
