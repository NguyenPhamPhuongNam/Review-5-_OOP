class IntArr {
private:
    int count;    
    int* values; 

public:
    // Constructor mac dinh
    IntArr() : count(0), values(nullptr) {}


    IntArr(int n, int defaultValue = 0) : count(n), values(nullptr) {
        if (n > 0) {
            values = new int[n];
            for (int i = 0; i < n; ++i) {
                values[i] = defaultValue;
            }
        }
    }

    // Destructor
    ~IntArr() {
        delete[] values;
    }

    // Copy constructor
    IntArr(const IntArr& other) : count(other.count), values(nullptr) {
        if (count > 0) {
            values = new int[count];
            for (int i = 0; i < count; ++i) {
                values[i] = other.values[i];
            }
        }
    }


    IntArr& operator=(const IntArr& other) {
        if (this != &other) {
            delete[] values;  

            count = other.count;
            values = (count > 0) ? new int[count] : nullptr;

            for (int i = 0; i < count; ++i) {
                values[i] = other.values[i];
            }
        }
        return *this;
    }

    IntArr concat(const IntArr& other) const {
        IntArr result(count + other.count);
        for (int i = 0; i < count; ++i) {
            result.values[i] = values[i];
        }
        for (int i = 0; i < other.count; ++i) {
            result.values[count + i] = other.values[i];
        }
        return result;
    }


    void push(int value) {
        int* newValues = new int[count + 1];
        for (int i = 0; i < count; ++i) {
            newValues[i] = values[i];
        }
        newValues[count] = value;
        delete[] values;
        values = newValues;
        count++;
    }


    friend istream& operator>>(istream& in, IntArr& arr) {
        int n;
        cout << "Enter number of elements: ";
        in >> n;

        delete[] arr.values;  
        arr.values = (n > 0) ? new int[n] : nullptr;
        arr.count = n;

        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; ++i) {
            in >> arr.values[i];
        }
        return in;
    }


    friend ostream& operator<<(ostream& out, const IntArr& arr) {
        out << "[ ";
        for (int i = 0; i < arr.count; ++i) {
            out << arr.values[i] << " ";
        }
        out << "]";
        return out;
    }
};
