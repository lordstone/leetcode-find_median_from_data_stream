class MedianFinder {
public:

    vector<int> maxHeap;//first to add
    vector<int> minHeap;

    void maxHeapify(){
        if (maxHeap.size() <= 1) return;
        int lvl = maxHeap.size() - 1;
        while (lvl >= 1){
            if(maxHeap[(lvl - 1)/2] < maxHeap[lvl]){
                int tmp = maxHeap[lvl];
                maxHeap[lvl] = maxHeap[(lvl - 1)/2];
                maxHeap[(lvl - 1)/2] = tmp;
            }else{
                return;
            }
            lvl = (lvl - 1) / 2;
        }
    }//end maxHeapify

    void minHeapify(){
        if (minHeap.size() <= 1) return;
        int lvl = minHeap.size() - 1;
        while (lvl >= 1){
            if(minHeap[(lvl - 1)/2] > minHeap[lvl]){
                int tmp = minHeap[lvl];
                minHeap[lvl] = minHeap[(lvl - 1)/2];
                minHeap[(lvl - 1)/2] = tmp;
            }else{
                return;
            }
            lvl = (lvl - 1) / 2;
        }
    }//end minHeapify

    int extractMin(){
        int tmp2 = minHeap[0];
        minHeap[0] = minHeap[minHeap.size() - 1];
        minHeap.pop_back();
        int lvl = 0;
        //int ptr = minHeap.size() - 1;
        while (  (2 * lvl + 1) < minHeap.size() ){//lvl <= (minHeap.size() ) / 2 -1){
            bool myflag = false;
            if(2 * lvl + 2 < minHeap.size()){
                int index = 2 * lvl + 1;
                if(minHeap[2*lvl+1] > minHeap[2*lvl+2]) index ++;
                if(minHeap[lvl] > minHeap[index]){
                    int tmp = minHeap[lvl];
                    minHeap[lvl] = minHeap[index];
                    minHeap[index] = tmp;
                    lvl = index;
                    myflag = true;
                }//end if
            }else{
                if(minHeap[lvl] > minHeap[2*lvl+1]){
                    int tmp = minHeap[lvl];
                    minHeap[lvl] = minHeap[2*lvl+1];
                    minHeap[2*lvl+1] = tmp;
                    lvl = 2*lvl+1;
                    myflag = true;
                }//end if
            }
            if(!myflag) return tmp2;
        }
        return tmp2;
    }//end extractmin

    int extractMax(){
        int tmp2 = maxHeap[0];
        maxHeap[0] = maxHeap[maxHeap.size() - 1];
        maxHeap.pop_back();
        int lvl = 0;
        //int ptr = maxHeap.size() - 1;
        while ((2 * lvl + 1) < maxHeap.size()){
            bool myflag = false;
            if(2 * lvl + 2 < maxHeap.size()){
                int index = 2 * lvl + 1;
                if(maxHeap[2*lvl+1] < maxHeap[2*lvl+2]) index ++;
                if(maxHeap[lvl] < maxHeap[index]){
                    int tmp = maxHeap[lvl];
                    maxHeap[lvl] = maxHeap[index];
                    maxHeap[index] = tmp;
                    lvl = index;
                    myflag = true;
                }//end if
            }else{
                if(maxHeap[lvl] < maxHeap[2*lvl+1]){
                    int tmp = maxHeap[lvl];
                    maxHeap[lvl] = maxHeap[2*lvl+1];
                    maxHeap[2*lvl+1] = tmp;
                    lvl = 2*lvl+1;
                    myflag = true;
                }//end if
            }
            if(!myflag) return tmp2;
        }
        return tmp2;
    }//end extractmax


    // Adds a number into the data structure.
    void addNum(int num) {
        if(maxHeap.size() == 0 && minHeap.size() == 0) {
            maxHeap.push_back(num);
            return;
        }// if first num to add
        if(maxHeap.size() <= minHeap.size()){
            if(num > minHeap[0]){
                minHeap.push_back(num);
                minHeapify();
                maxHeap.push_back(extractMin());
                maxHeapify();
                //return;
            }else{
                maxHeap.push_back(num);
                maxHeapify();
                //return;
            }
        }else{
            if(num < maxHeap[0]){
                maxHeap.push_back(num);
                maxHeapify();
                minHeap.push_back(extractMax());
                minHeapify();
                //return;
            }else{
                minHeap.push_back(num);
                minHeapify();
                //return;
            }
        }
        if(maxHeap.size()>minHeap.size() + 1){
            minHeap.push_back(extractMax());
            minHeapify();
        }else if(minHeap.size()>maxHeap.size()){
            maxHeap.push_back(extractMin());
            maxHeapify();
        }
    }

    // Returns the median of current data stream
    double findMedian() {
        if(maxHeap.size() + minHeap.size() == 0) return 0;//err case
        if((maxHeap.size() + minHeap.size()) % 2 == 1){
            return  maxHeap[0];
        }else{
            return (maxHeap[0] + minHeap[0])/2.0;
        }
    }
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();
