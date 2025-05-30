#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <cstddef> // for size_t

//funkcijos, kurias reikia igyvendinti:
/*
push_back() x

pop_back() x

insert() x 

erase() x

clear() x

resize() x

at() x 

operator[] x 

front()  x

back() x

size() x

capacity() x

empty() x

max_size() x

shrink_to_fit() x

reserve() x

begin() x

end() x
*/

template <typename A>
class Vector {
    private:
        A* data_; // Rodykle i bet kokio tipo A konteineri
        size_t size_; // Talpa, kiek elementų yra saugoma
        size_t capacity_; // Talpa, kiek elementų gali būti saugoma be perskirstymo

        void resize(size_t new_capacity) {
            A* new_data = new A[new_capacity];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
            capacity_ = new_capacity;
        }

    public:
        Vector() : data_(nullptr), size_(0), capacity_(0) {} // Default konstruktorius

        Vector(size_t initial_capacity) : size_(0), capacity_(initial_capacity) { // Konstruktorius su pradiniu dydziu
            if (capacity_ > 0) {
                data_ = new A[capacity_];
            } else {
                data_ = nullptr;
            }
        }
        //konstruktorius su dviem kintamaisiais parametrais
        Vector(size_t initial_size, A value) : size_(initial_size), capacity_(initial_size) {
            data_ = new A[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = value; // Užpildome vektorių pradine reikšme
            }
        }

        //konstruktorius su aibe
        Vector(std::initializer_list<A> init) : size_(init.size()), capacity_(init.size()) {
            data_ = new A[capacity_];
            size_t i = 0;
            for (const auto& value : init) {
                data_[i++] = value;
            }
        }

        Vector(const Vector& other) : size_(other.size_), capacity_(other.capacity_) { // Copy konstruktorius
            data_ = new A[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }

        Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_) { // Move konstruktorius
            other.data_ = nullptr;
            other.size_ = 0;
            other.capacity_ = 0;
        }

        ~Vector() { // Destruktorius
            delete[] data_;
        }

        //=================operatoriai========================
        Vector& operator=(const Vector& other) { // Copy priskyrimo operatorius
            if (this != &other) {
                delete[] data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                data_ = new A[capacity_];
                for (size_t i = 0; i < size_; ++i) {
                    data_[i] = other.data_[i];
                }
            }
            return *this;
        }

        Vector& operator=(Vector&& other) noexcept { // Move priskyrimo operatorius
            if (this != &other) {
                delete[] data_;
                data_ = other.data_;
                size_ = other.size_;
                capacity_ = other.capacity_;
                other.data_ = nullptr;
                other.size_ = 0;
                other.capacity_ = 0;
            }
            return *this;
        }

        A& operator[](size_t index) { // Indeksavimo operatorius, leidžiantis pasiekti elementus pagal indeksą
            return data_[index];
        }

        const A& operator[](size_t index) const { // Const versija indeksavimo operatoriaus
            return data_[index];
        }
        
        //=================metodai========================

        void push_back(A value) {
            if (size_ >= capacity_) {
                resize(capacity_ == 0 ? 1 : capacity_ * 2);
            }
            data_[size_++] = value;
        }

        void pop_back() {
            if (size_ > 0) {
                --size_;
            }
        }

        void insert(size_t index, A value) {
            for (size_t i = size_; i > index; --i) {
                data_[i] = data_[i - 1]; // Perkeliame elementus vienu indeksu i desine (is galo)
            }
            data_[index] = value;
            ++size_;
        }

        void erase(size_t index) { //vieno elemento istrynimas is pasirinktos vietos
            for (size_t i = index; i < size_ - 1; ++i) {
                data_[i] = data_[i + 1]; // Perkeliame elementus vienu indeksu i kaire
            }
            --size_;
        }

        void erase(size_t start, size_t end) { // keliu elementu istrynimas nuo start iki end
            size_t count = end - start + 1;
            for (size_t i = start; i < size_ - count; ++i) {
                data_[i] = data_[i + count]; // Perkeliame elementus vienu indeksu i kaire
            }
            size_ -= count;
        }

        void clear() {
            size_ = 0; // duomenu neisvalome (nenunulinam ar panasiai), tik nurodome, kad dydis yra 0.
        }

        A& at(size_t index) {
            return data_[index];
        }

        A& front(){
            return data_[0];
        }

        A& back() {
            return data_[size_-1]; // indeksavimas vyksta nuo 0 dazniausiai
        }

        bool empty() const {
            return size_==0 ? true : false;
        }

        size_t max_size() const {
            return std::numeric_limits<size_t>::max() / sizeof(A); // Maksimalus dydis, kurį gali turėti vektorius
        }

        void shrink_to_fit() {
            if (size_<capacity_){
                capacity_ = size_; // Sumažiname talpą iki esamo dydžio
            }
        }

        void reserve(size_t new_capacity) {
            if (new_capacity > capacity_) {
                resize(new_capacity); // Padidiname talpą, jei reikia
            }
        }

        A* begin() {
            return data_; // Grąžina rodyklę į pirmą elementą
        }

        A* end() {
            return data_ + size_; // Grąžina rodyklę į vieną po paskutinio elemento
        }

        size_t size() const {
            return size_;
        }        
        
        size_t capacity() const {
            return capacity_;
        }

        //=================kiti metodai======================== (neveikia v1.5)

        void sort(bool (*compare)(const A&, const A&)) {
            std::sort(data_, data_ + size_, compare); // Rikiuoja elementus pagal pateiktą palyginimo funkciją
        }
};

#endif // VECTOR_HPP