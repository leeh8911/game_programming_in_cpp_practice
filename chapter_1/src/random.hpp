/*!
 * @file random.hpp
 * @author sangwon lee (leeh8911@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-04-15
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef RANDOM_HPP_
#define RANDOM_HPP_

#include <Eigen/Dense>
#include <SFML/Graphics.hpp>
#include <initializer_list>
#include <random>
#include <type_traits>

namespace gmlib
{
class RandomGenerator
{
 public:
    RandomGenerator() = default;

    static void setSeed(unsigned int seed)
    {
        mGenerator.seed(seed);
    }
    static std::random_device& getRandomDevice()
    {
        return mRandomDevice;
    }

 private:
    static std::random_device mRandomDevice;
    static std::mt19937 mGenerator;
};

template <typename T, bool = std::is_integral<T>::value, bool = std::is_floating_point<T>::value>
struct RandomHelper : public RandomGenerator
{
};

template <typename T> struct RandomHelper<T, true, false> : public RandomGenerator
{
    static T Uniform(T min, T max)
    {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(getRandomDevice());
    }
};

template <typename T> struct RandomHelper<T, false, true> : public RandomGenerator
{
    static T Uniform(T min, T max)
    {
        std::uniform_real_distribution<T> distribution(min, max);
        return distribution(getRandomDevice());
    }

    static T Normal(T mean, T stddev)
    {
        std::normal_distribution<T> distribution(mean, stddev);
        return distribution(getRandomDevice());
    }
};

class Random : public RandomGenerator
{
 public:
    template <typename T> static T Uniform(T min, T max)
    {
        return RandomHelper<T>::Uniform(min, max);
    }

    template <typename T>
    static std::vector<T> UniformVector(std::initializer_list<T> min, std::initializer_list<T> max)
    {
        if (min.size() != max.size())
        {
            throw std::invalid_argument("min and max size must be same");
        }

        std::vector<T> result(min.size());
        auto result_it = result.begin();
        auto min_it = min.begin();
        auto max_it = max.begin();
        for (; min_it != min.end(); ++min_it, ++max_it, ++result_it)
        {
            *result_it = RandomHelper<T>::Uniform(*min_it, *max_it);
        }
        return result;
    }

    template <typename T> static sf::Vector2<T> UniformVector(sf::Vector2<T> min, sf::Vector2<T> max)
    {
        return {Uniform(min.x, max.x), Uniform(min.y, max.y)};
    }

    template <typename T> static T Normal(T mean, T stddev)
    {
        return RandomHelper<T>::Normal(mean, stddev);
    }

    template <typename T>
    static std::vector<T> NormalVector(std::initializer_list<T> mean, std::initializer_list<T> stddev)
    {
        if (mean.size() != stddev.size())
        {
            throw std::invalid_argument("mean and stddev size must be same");
        }

        std::vector<T> result(mean.size());
        auto result_it = result.begin();
        auto mean_it = mean.begin();
        auto stddev_it = stddev.begin();
        for (; mean_it != mean.end(); ++mean_it, ++stddev_it, ++result_it)
        {
            *result_it = RandomHelper<T>::Normal(*mean_it, *stddev_it);
        }
        return result;
    }

    template <typename T> static sf::Vector2<T> NormalVector(sf::Vector2<T> mean, sf::Vector2<T> stddev)
    {
        return {Normal(mean.x, stddev.x), Normal(mean.y, stddev.y)};
    }
};

} // namespace gmlib
#endif // RANDOM_HPP_
