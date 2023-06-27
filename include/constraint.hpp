#ifndef CONSTRAINT_H_
#define CONSTRAINT_H_

#include "eigen3/Eigen/Core"
#include <eigen3/Eigen/src/Core/Matrix.h>

class Constraint {

    public:
        virtual unsigned int getDoF() const = 0;

        virtual float evaluateConstraint() const = 0;

        virtual Eigen::VectorXf evaluateJacobian() = 0;

        virtual Eigen::MatrixXf getInvMass() = 0;

        virtual void updateSystem(const Eigen::VectorXf& deltax) = 0;

        inline float getComplience() const { return complience; };

    private:
        float complience = 0.0f;        // set to zero for hard constraints

};

#endif // CONSTRAINT_H_
