package Graph;

/**
 * Created by ghost on 24/10/2016.
 */
public class Edge {
    public Vertex nextConnected;

    public Edge() {}

    public Edge(Vertex nextConnected)
    {
        this.nextConnected = nextConnected;
    }

    public void setNextConnected(Vertex nextConnected){this.nextConnected = nextConnected;}
    public Vertex getNextConnected(){return this.nextConnected;}
}
