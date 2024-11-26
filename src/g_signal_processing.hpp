#pragma once

namespace gbase {

class GFilter {
  public:
    virtual ~GFilter() = default;

    virtual double filter(double input) = 0;
    virtual void reset() = 0;
    virtual double current() const = 0;
};

class GLowPassFilter : public GFilter {
  public:
    explicit GLowPassFilter(double alpha) : GFilter(), alpha_{alpha} {}

    double filter(double input) override {
        previous_ = current_;
        current_ = alpha_ * input + (1.0 - alpha_) * previous_;
        return current_;
    }

    void reset() override {
        previous_ = 0.0;
        current_ = 0.0;
    }

    double current() const override { return current_; }

  private:
    double alpha_{0.0};
    double previous_{0.0};
    double current_{0.0};
};

} // namespace gbase