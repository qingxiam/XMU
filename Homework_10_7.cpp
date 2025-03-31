#include &lt;vector&gt;
#include &lt;algorithm&gt;
using namespace std;
struct Fragment {
    int totalLength;
    int fragmentOffset;
};
vector<Fragment> fragmentPacket(int originalSize, const vector<int>& mtuList) {
    vector<Fragment> fragments;
    if(mtuList.empty()) return fragments;
    int smallestMTU = *min_element(mtuList.begin(), mtuList.end());
    const int ipHeader = 20;
    int totalSizeWithHeader = originalSize + ipHeader;
    if(totalSizeWithHeader <= smallestMTU) {
        fragments.push_back({totalSizeWithHeader, 0});
        return fragments;
    }
    int maxPayload = smallestMTU - ipHeader;
    if(maxPayload <= 0) return fragments;
    int adjustedPayload = (maxPayload / 8) * 8;
    if(adjustedPayload <= 0) return fragments;
    if(originalSize == 0) {
        if(ipHeader <= smallestMTU) {
            fragments.push_back({ipHeader, 0});
        }
        return fragments;
    }
    int fragmentCount = (originalSize + adjustedPayload - 1) / adjustedPayload;
    for(int i = 0; i < fragmentCount; ++i) {
        int currentData;
        if(i < fragmentCount - 1) {
            currentData = adjustedPayload;
        } else {
            currentData = originalSize - i * adjustedPayload;
        }
        int offsetValue = (i * adjustedPayload) / 8;
        int totalFragmentSize = currentData + ipHeader;
        fragments.push_back({totalFragmentSize, offsetValue});
    }
    return fragments;
}
