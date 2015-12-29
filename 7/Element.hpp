#ifndef ELEMENT
#define ELEMENT
#include <memory>
#include <vector>
#include <map>
#include <iostream>

enum class State {
  UNDEFINED, DEFINED
};

class Element : public std::enable_shared_from_this<Element> {
public:

  virtual ~Element() {
    this->inputs_.clear();
    this->outputs_.clear();
  }

  void addOutput(std::shared_ptr<Element> elementPtr) {
    this->outputs_.push_back(elementPtr);
    elementPtr->addInput(this->getPtr());
    if(this->state_ == State::DEFINED) {
      elementPtr->inputChanged();
    }
  }

  unsigned short int getValue() {
    return this->value_;
  }

protected:

  void setValue(unsigned short int value) {
    if(this->state_ == State::DEFINED) {
      return;
    }
    this->state_ = State::DEFINED;
    this->value_ = value;
    for(auto& output : outputs_) {
      output->inputChanged();
    }
  }

  virtual void inputChanged() {
    std::vector<unsigned short int> values;
    for(auto& input : inputs_) {
      std::shared_ptr<Element> i = input.lock();
      if(i->getState() == State::UNDEFINED) {
	return;
      }
      values.push_back(i->getValue());
    }
    calculateValue(values);
  }

  virtual void calculateValue(const std::vector<unsigned short int>& values) = 0;

private:
  unsigned short int value_ = 0;
  State state_ = State::UNDEFINED;
  std::vector<std::shared_ptr<Element>> outputs_;
  std::vector<std::weak_ptr<Element>> inputs_;

  std::shared_ptr<Element> getPtr() {
    return shared_from_this();
  }

  void addInput(std::weak_ptr<Element> elementPtr) {
    this->inputs_.push_back(elementPtr);
  }

  State getState() {
    return this->state_;
  }

};

class Signal : public Element {
public:
  Signal(unsigned short int value) {
    setValue(value);
  }

  ~Signal() {}

protected:
  void inputChanged() override {}
  void calculateValue(const std::vector<unsigned short int>& values) override {}
};

class Wire : public Element {
public:

  ~Wire() {}

protected:
  void calculateValue(const std::vector<unsigned short int>& values) override {
    setValue(values[0]);
  }
};

class And : public Element {
public:
  ~And() {}
protected:
  void calculateValue(const std::vector<unsigned short int>& values) override {
    if(values.size() < 2)
      return;
    unsigned short int output = 0xffff;
    for(auto& value : values) {
      output &= value;
    }
    setValue(output);
  }
};

class Or : public Element {
public:
  ~Or() {}
protected:
  void calculateValue(const std::vector<unsigned short int>& values) override {
    if(values.size() < 2)
      return;
    unsigned short int output = 0x0000;
    for(auto& value : values)
      output |= value;
    setValue(output);
  }
};

class Not : public Element {
public:
  ~Not() {}
protected:
  void calculateValue(const std::vector<unsigned short int>& values) override {
    setValue(~values[0]);
  }
};

class LShift : public Element {
public:
  ~LShift() {}
protected:
  void calculateValue(const std::vector<unsigned short int>& values) override {
    if(values.size() < 2)
      return;
    setValue(values[0] << values[1]);
  }
};

class RShift : public Element {
public:
  ~RShift() {}
protected:
  void calculateValue(const std::vector<unsigned short int>& values) override {
    if(values.size() < 2)
      return;
    setValue(values[0] >> values[1]);
  }
};

class Circuit {
public:

  std::shared_ptr<Wire> getWire(const std::string& name) {
    const auto& it = wires_.find(name);
    if(it != wires_.end()) {
      return it->second;
    } else {
      return std::shared_ptr<Wire>(nullptr);
    }
  } 

  std::shared_ptr<Element> buildSignal(unsigned short int value) {
    auto signalPtr = std::make_shared<Signal>(value);
    elements_.push_back(signalPtr);
    return signalPtr;
  }

  std::shared_ptr<Element> buildWire(const std::string& name) {
    auto wirePtr = std::make_shared<Wire>();
    wires_[name] = wirePtr;
    return wirePtr;
  }

  std::shared_ptr<Element> buildAnd() {
    return build<And>();
  }

  std::shared_ptr<Element> buildOr() {
    return build<Or>();
  }

  std::shared_ptr<Element> buildNot() {
    return build<Not>();
  }

  std::shared_ptr<Element> buildLShift() {
    return build<LShift>();
  }

  std::shared_ptr<Element> buildRShift() {
    return build<RShift>();
  }

  void print() {
    for(auto& elem : wires_) {
      std::cout << elem.first << ", " << elem.second->getValue() << std::endl;
    }
  }
private:
  template <class T>
  std::shared_ptr<Element> build() {
    auto ptr = std::make_shared<T>();
    elements_.push_back(ptr);
    return ptr;
  }

  std::vector<std::shared_ptr<Element>> elements_;
  std::map<std::string, std::shared_ptr<Wire>> wires_;
};

#endif // ELEMENT
