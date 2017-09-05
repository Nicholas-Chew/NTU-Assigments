package Main;

import Graph.*;

/**
 * Created by ghost on 24/10/2016.
 */
public class dataGen {
    static Graph g;

    public static Graph Generate(int size, int edgeSize)
    {
        g = new Graph(size);

        for(int i=0; i<edgeSize; i++)
        {
            int random = (int)(Math.random() * size);
            int random2 = (int)(Math.random() * size);
            if (!inTheList(random, random2)&& random !=random2)
            {
                g.nodes[random].edge.add(new Edge(g.nodes[random2]));
                g.nodes[random2].edge.add(new Edge(g.nodes[random]));
            }
            else
                i--;
        }

        return g;
    }

    private static boolean inTheList(int index, int containIndex)
    {
        for (Edge ed:
             g.nodes[index].edge) {
            if (ed.nextConnected.index ==  containIndex)
                return true;
        }

        return false;
    }
}
