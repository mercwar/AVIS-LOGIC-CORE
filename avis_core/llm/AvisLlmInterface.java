package llm;

import com.sun.jna.Library;

public interface AvisLlmInterface extends Library {
    int force_memory_context_refresh(String log_json_data, long allocation_bytes);
}
