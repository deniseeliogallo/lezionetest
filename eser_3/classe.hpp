#include <concepts>
#include <iostream>
#include <numeric>

template<typename T> requires std::integral<T>
class rational
{
	T num_;
	T den_;

public:

	/*Costruttore di default*/
 rational(): num_(0),den_(1){}

	/*Costruttore user-defined*/
 rational(T numerator, T denominator) : num_(numerator), den_(denominator) {
	 semplifica();
 }
 
 /* Restituiscono i valori di x e y */
    T num() const { return num_; }
    T den() const { return den_; }

/* Controllo NaN: numeratore e denominatore entrambi zero */
    bool is_nan() const {
        return (num_ == 0 && den_ == 0);
    }

 /* Controllo Inf: solo il denominatore è zero */
    bool is_inf() const {
        return (num_ != 0 && den_ == 0);  //da true o false in base
    }
	
/* facciamo una semplifica: troviamo il MCD di numeratore e denominatore e poi ce lo dividiamo */
	void semplifica() {
        if (den_ == 0) return; 
        T MCD = std::gcd(num_, den_);
        num_ /= MCD;
        den_ /= MCD;
	}
		
/* Implementazione canonica della somma */
    rational& operator+=(const rational& other) {
		
		if (this->is_nan() || other.is_nan()) { // nan + numero = nan
        num_ = 0;
        den_ = 0; 
        return *this;
		}
		
		if (this->is_inf() || other.is_inf()) { // inf + numero = inf
        num_ = 1;
        den_ = 0;
        return *this;
		}
		
		//in altro caso somma tra frazioni normali 
		num_ = (num_ * other.den_) + (other.num_ * den_);
        den_ = den_ * other.den_;
		
		//probabilmente avremo multipli sotto e sopra - semplifichiamo la frazione
        semplifica();
		return *this;
    }
    
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }
	
	/* Implementazione canonica della sottrazione */
    rational& operator-=(const rational& other) {
		//uguale alla somma
		if (this->is_nan() || other.is_nan()) {
        num_ = 0;
        den_ = 0;
        return *this;
		}
		
		if (this->is_inf() || other.is_inf()) {
        num_ = 1;
        den_ = 0;
        return *this;
		}
		
        num_ = (num_ * other.den_) - (other.num_ * den_);
        den_ = den_ * other.den_;
		semplifica();
        return *this;
    }
    
    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other; 
        return ret;
    }
	
	/* Implementazione canonica della moltiplicazione */
    rational& operator*=(const rational& other) {
		if (this->is_nan() || other.is_nan()) { //Nan * num = Nan
        num_ = 0;
        den_ = 0;
        return *this;
		}
		
		//inf * num = inf
		//in realtà questo vale solo se num è diverso da 0 - in tal caso abbiamo nan
		
		if ((this->is_inf() && other.num_ == 0) || (other.is_inf() && this->num_ == 0)) {
        num_ = 0; den_ = 0;
        return *this;
		}
		
		if (this->is_inf() || other.is_inf()) {
        num_ = 1;
        den_ = 0;
        return *this;
		}
		
        num_ = num_ * other.num_;
        den_ = den_ * other.den_;
		semplifica();
        return *this;
    }
    
    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other; 
        return ret;
    }
	
	/* Implementazione canonica della divisione */
    rational& operator/=(const rational& other) {
		
		// nan / num o vsa da nan
		if (this->is_nan() || other.is_nan()) {
        num_ = 0;
        den_ = 0;
        return *this;
		}
		
		// dividendo per 0 otteniamo infinito 
		if (other.num_ == 0 && other.den_ != 0) {
        num_ = 1; den_ = 0;
        return *this;
		}
		
		// facendo 0/inf otteniamo 0 - per semplicità metto den=1
		if (this->num_ == 0 && other.is_inf()) {
        num_ = 0; den_ = 1;
        return *this;
		}
		
        num_ = num_ * other.den_;
        den_ = den_ * other.num_;
		semplifica();
        return *this;
    }
    
    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
	
	
};

/* implemento la stampa */
	template<typename T>
	std::ostream& 
	operator<<(std::ostream& os, const rational<T>& r) 
{
	if (r.is_nan()) os << "NaN";
    else if (r.is_inf()) os << "Inf";
    else os << "(" << r.num() << "/" << r.den() << ")";
    return os;
}


