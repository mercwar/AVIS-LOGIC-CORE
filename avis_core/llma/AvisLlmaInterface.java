package llma;

import com.sun.jna.Library;

public interface AvisLlmaInterface extends Library {
    int verify_agent_trajectories(int[] route_nodes, int depth, float minimum_threshold);
}
