package gguf;

import com.sun.jna.Library;
import com.sun.jna.Structure;
import java.util.Arrays;
import java.util.List;

public interface AvisGgufInterface extends Library {
    public static class GgufKvPair extends Structure {
        public byte[] token_key_string = new byte[64];
        public int metadata_value_register;

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList("token_key_string", "metadata_value_register");
        }
    }
    int inject_avis_metadata_block(String file_path, GgufKvPair kv_data);
}
