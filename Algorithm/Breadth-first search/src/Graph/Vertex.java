package Graph;

import java.util.ArrayList;

/**
 * Created by ghost on 24/10/2016.
 */
public class Vertex {
    public int index;
    public boolean visited = false;
    public ArrayList<Edge> edge;

    public Vertex()
    {

    }

    public Vertex(int index)
    {
        this.index = index;
        this.edge = new ArrayList<>();
    }

    public void setIndex (int index){this.index = index;}
    public void setVisited (boolean visited){this.visited = visited;}
    public void setEdge (ArrayList<Edge> edge){this.edge = edge;}

    public int getIndex (){return  this.index;}
    public boolean getVisited() {return this.visited;}
    public ArrayList<Edge> getEdge() {return this.edge;}

}
