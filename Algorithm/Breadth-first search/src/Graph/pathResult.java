package Graph;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.util.ArrayList;
import java.util.Collections;

/**
 * Created by ghost on 24/10/2016.
 */
public class pathResult {

    public Vertex startNode;
    public Vertex endNode;
    public ArrayList<Vertex> path = new ArrayList<>();
    public int pathLength = -1;
    public String fileName = "";

    public pathResult()
    {
    }

    public pathResult(String fileName)
    {
        this.fileName = fileName;
    }

    public void addPath(Vertex i)
    {
        path.add(i);
        pathLength++;
    }

    public void writeResult()
    {
        if(fileName != "") {
            BufferedWriter writer = null;
            try {
                writer = new BufferedWriter(new FileWriter(System.getProperty("user.dir") + "/Data/" + fileName+".txt", true));
                if(pathLength != -9999) {
                    writer.write("From Node " + startNode.index + " to " + endNode.index + "\tLength:" + pathLength);
                    writer.newLine();

                    for (int i = 0; i < path.size(); i++) {
                        writer.write(path.get(i).getIndex() + " ");
                        if (i != path.size() - 1)
                            writer.write("-> ");
                    }
                    writer.newLine();
                    //writer.write("-----------------------------------------------------------------------------------------------");
                    //writer.newLine();
                    writer.newLine();
                }
                else
                {
                    writer.write("From Node " + startNode.index + " to " + endNode.index + "\tLength: Nil");
                    writer.newLine();
                    //writer.write("-----------------------------------------------------------------------------------------------");
                    //writer.newLine();
                    writer.newLine();
                }

            } catch (Exception e) {

            }finally {
                try {
                    writer.close();
                }
                catch (Exception e)
                {

                }
            }
        }

    }

    public void reverse()
    {
        Collections.reverse(path);
    }
}
