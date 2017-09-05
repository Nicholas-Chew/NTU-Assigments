package Graph;


/**
 * Created by ghost on 24/10/2016.
 */
public class Graph{
    public Vertex[] nodes;
    public int size;

    public  Graph()
    {}


    public Graph(int size)
    {
        nodes = new Vertex[size];
        this.size = size;

        for(int i = 0; i<size; i++)
        {
            nodes[i] = new Vertex(i);
        }
    }

    public void clearAllFlag()
    {
        for(int i = 0; i<size; i++)
        {
            nodes[i].visited = false;
        }
    }


    public void setNodes(Vertex[] nodes)
    {
        this.nodes = nodes;
    }

    public void setSize(int size)
    {
        this.size = size;
    }


    public Vertex[] getNodes()
    {
        return this.nodes ;
    }

    public int getSize()
    {
        return this.size ;
    }

}

