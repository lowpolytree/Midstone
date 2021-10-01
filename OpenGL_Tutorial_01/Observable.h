#pragma once
#include <string>
#include <vector>
template <typename> class Observer;

template<typename T>
class Observable
{
public:
	void notify(T& source, const std::string& propertyName);
	void subscribe(Observer<T>& observer);
	void unsubscribe(Observer<T>& observer);
private:
	std::vector<Observer<T>*> observers;
};

template<typename T>
void Observable<T>::notify(T& source, const std::string& propertyName)
{
	for (auto observer : observers) {
		observer->propertyChanged(source, propertyName);
	}
}

template<typename T>
void Observable<T>::subscribe(Observer<T>& observer)
{
	observers.push_back(&observer);
}

template<typename T>
void Observable<T>::unsubscribe(Observer<T>& observer)
{
	auto removed = remove(observers.begin(), observers.end(), &observer);
	observers.erase(removed, observers.end());
}