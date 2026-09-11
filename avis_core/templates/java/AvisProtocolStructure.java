package templates.java;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class AvisProtocolStructure {
    
    public static class AvisWrapperConfig {
        public String magicHeader;
        public String targetAppId;
        public String binarySource;
        public String interfaceBind;
        public Map<String, String> protocolParameters = new HashMap<>();

        @Override
        public String toString() {
            return "AVIS Module Config [" + targetAppId + "]\n" +
                   " -> Binary: " + binarySource + "\n" +
                   " -> Java Interface: " + interfaceBind + "\n" +
                   " -> Metrics Loaded: " + protocolParameters;
        }
    }

    public static class SystemOrchestrationChain {
        public String version;
        public String securityProfile;
        public List<String> pipelineStages = new ArrayList<>();
    }
}
