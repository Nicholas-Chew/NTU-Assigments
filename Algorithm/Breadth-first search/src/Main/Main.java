package Main;

import Graph.*;


import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;



/**
 * Created by ghost on 24/10/2016.
 */
public class Main {

    private static long  startTime = 0;
    private static long  totalTimeTaken = 0;
    private static int   count = 0;
    private static int[] setA = {5000,10000};
    private static int[] edgeA = {1000, 5000, 10000, 50000, 100000};

    public static void main(String[] args)
    {
        //Graph g = dataGen.Generate(5,0);
        //testRoutine(g,0);

        mainTest();
    }

    private static void  mainTest()
    {
        int i,j;

        for(i = 0;i < 2; i++) {
            for(j = 0; j< 5; j ++) {

                Graph g = dataGen.Generate(setA[i], edgeA[j]);

                testRoutine(g, edgeA[j]);
                //System.out.println("Graph with Vertex " + setA[i] / 1000 + "k and " + edgeA[j] / 1000 + "k edges\nTotal computing time: " + sec / 1000000000 + " sec \nAvg computing time: " + sec / count + " nano sec\n");

            }
        }
    }


    private static void testRoutine(Graph g, int edgeS) {
        int i, j;
        int s = g.size;
        String fileName = "G" + s + "_E" + edgeS;
        ArrayList<pathResult> result = new ArrayList<>();

        totalTimeTaken = 0;
        count = 0;

        for (i = 0; i < s; i++) {
            for (j = i + 1; j < s; j++) {
                count++;
                startTime = System.nanoTime();
                result.add(bfs.search(g, i, j, fileName));
                totalTimeTaken += (System.nanoTime() - startTime);
                g.clearAllFlag();
            }
        }

        writeArray(result,fileName);

        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(System.getProperty("user.dir") + "/Data/" + fileName + ".txt", true));

            writer.write("Total Time Taken:" + totalTimeTaken/1000000000 + "sec\t Average Time Taken:" + totalTimeTaken / count+" nano Sec");
            writer.newLine();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        } finally {
            try {
                writer.close();
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }

    private static void writeArray (ArrayList<pathResult> ans, String fileName)
    {
        String separator = System.getProperty("line.separator");
        String fullString ="";
        BufferedWriter writer = null;
        try {
            writer = new BufferedWriter(new FileWriter(System.getProperty("user.dir") + "/Data/" + fileName + ".txt", true));

        for (pathResult res: ans) {
            fullString = "";
            if (res.pathLength != -9999) {
                fullString += "From Node " + res.startNode.index + " to " + res.endNode.index + "\tLength:" + res.pathLength + separator;

                for (int i = 0; i < res.path.size(); i++) {
                    fullString += res.path.get(i).getIndex() + " ";
                    if (i != res.path.size() - 1)
                        fullString += "-> ";
                }

            } else {
                fullString += "From Node " + res.startNode.index + " to " + res.endNode.index + "\tLength: Nil";
            }
            fullString += separator + separator;

            writer.write(fullString);
        }

        } catch (Exception e) {

        } finally {
            try {
                writer.close();
            } catch (Exception e) {

            }
        }
    }

}
