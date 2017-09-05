package Main;

import Graph.*;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Map;
import java.util.HashMap;

/**
 * Created by ghost on 24/10/2016.
 */
public class bfs {

    public static pathResult search(Graph g, int start_index, int end_index, String fileName)
    {
        Vertex currentNode = null;
        pathResult result = new pathResult(fileName);
        Map<Vertex, Vertex> nextVertexMap = new HashMap<>();

        Queue<Vertex> queue = new LinkedList<>();
        queue.add(g.nodes[start_index]);
        queue.peek().visited = true;



        while(!queue.isEmpty())
        {
            currentNode = queue.poll();

            if(currentNode.index == end_index)
                break;

            for (Edge e: currentNode.edge)
            {
                if(!e.nextConnected.visited)
                {
                    e.nextConnected.visited = true;
                    queue.add(e.nextConnected);

                    nextVertexMap.put(e.nextConnected, currentNode);
                }
            }

        }

        result.startNode = g.nodes[start_index];
        result.endNode = g.nodes[end_index];

        if(currentNode.index != end_index) {
            result.pathLength = -9999;
            //result.writeResult();
            return result;
        }


        for(Vertex v = currentNode; v != null; v = nextVertexMap.get(v))
        {
            result.addPath(v);
        }

        result.reverse();
        //result.writeResult();
        return result;

    }

}
