// n2p2 - A neural network potential package
// Copyright (C) 2018 Andreas Singraber (University of Vienna)
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef SYMFNCBASECOMPANG_H
#define SYMFNCBASECOMPANG_H

#include "SymFncBaseComp.h"
#include <cstddef> // std::size_t
#include <string>  // std::string
#include <vector>  // std::vector

namespace nnp
{

/** Symmetry function class based on cutoff functions.
 *
 * Actual symmetry functions which make use of a dedicated cutoff function
 * derive from this class.
 */
class SymFncBaseCompAng : public SymFncBaseComp
{
public:
    /** Set symmetry function parameters.
     *
     * @param[in] parameterString String containing angular symmetry function
     *                            parameters.
     */
    virtual void        setParameters(std::string const& parameterString);
    /** Change length unit.
     *
     * @param[in] convLength Multiplicative length unit conversion factor.
     */
    virtual void        changeLengthUnit(double convLength);
    /** Get settings file line from currently set parameters.
     *
     * @return Settings file string ("symfunction_short ...").
     */
    virtual std::string getSettingsLine() const;
    // Core fcts
    bool                getCompactAngle(double  x,
                                        double& fx,
                                        double& dfx) const;
    bool                getCompactRadial(double  x,
                                         double& fx,
                                         double& dfx) const;
    /** Give symmetry function parameters in one line.
     *
     * @return String containing symmetry function parameter values.
     */
    virtual std::string parameterLine() const;
    /** Get description with parameter names and values.
     *
     * @return Vector of parameter description strings.
     */
    virtual std::vector<
    std::string>        parameterInfo() const;
    /** Get private #e1 member variable.
     */
    std::size_t         getE1() const;
    /** Get private #e2 member variable.
     */
    std::size_t         getE2() const;
    /** Get private #angleLeft member variable.
     */
    double              getAngleLeft() const;
    /** Get private #angleRight member variable.
     */
    double              getAngleRight() const;
    /** Calculate (partial) symmetry function value for one given distance.
     *
     * @param[in] distance Distance between two atoms.
     * @return @f$\left(e^{-\eta r^2} f_c(r)\right)^2@f$
     */
    virtual double      calculateRadialPart(double distance) const;
    /** Calculate (partial) symmetry function value for one given angle.
     *
     * @param[in] angle Angle between triplet of atoms (in radians).
     * @return @f$1@f$
     */
    virtual double      calculateAngularPart(double angle) const;
    /** Check whether symmetry function is relevant for given element.
     *
     * @param[in] index Index of given element.
     * @return True if symmetry function is sensitive to given element, false
     *         otherwise.
     */
    virtual bool        checkRelevantElement(std::size_t index) const;

protected:
    /// Element index of neighbor atom 1.
    std::size_t     e1;
    /// Element index of neighbor atom 2.
    std::size_t     e2;
    /// Left angle boundary.
    double          angleLeft;
    /// Right angle boundary.
    double          angleRight;
    /// Compact function member for angular part.
    CompactFunction ca;

    /** Constructor, initializes #type.
     */
    SymFncBaseCompAng(std::size_t type, ElementMap const&);
};

//////////////////////////////////
// Inlined function definitions //
//////////////////////////////////

inline std::size_t SymFncBaseCompAng::getE1() const { return e1; }
inline std::size_t SymFncBaseCompAng::getE2() const { return e2; }
inline double SymFncBaseCompAng::getAngleLeft() const { return angleLeft; }
inline double SymFncBaseCompAng::getAngleRight() const { return angleRight; }

}

#endif
