template <typename T>
class Obj;

template <typename T>
Obj<T> make_obj(T t);

template <typename T>
class Obj {
public:
struct test {
    T val;
};
    
private:
    T & t;
    Obj (T & t) : t(t) { }
    Obj() = delete;

    friend Obj make_obj<T>(T t);
};

template <typename T>
Obj<T> make_obj(T t) {
    typename Obj<T>::test a;
    return Obj<T>(t);
}

int main() {
	return 0;
}
