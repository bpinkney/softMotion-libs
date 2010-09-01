#ifndef QSOFTMOTIONPLANNER_H
#define QSOFTMOTIONPLANNER_H

#include <QMainWindow>
#include <string>
#include "curve.h"
#include "myPlot.h"
#include "ui_mainwindow.h"
#include "gbM/gbGENOM.h"




/** @mainpage QSoftMotionPlanner
 *
 * @section Copyright
 *
 * Copyright (c) 2010 LAAS/CNRS
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software for any purpose
 * with or without   fee is hereby granted, provided   that the above  copyright
 * notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS  SOFTWARE INCLUDING ALL  IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR  BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR  ANY DAMAGES WHATSOEVER RESULTING  FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION,   ARISING OUT OF OR IN    CONNECTION WITH THE USE   OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 *                                           Xavier BROQUERE on Feb 01 2010
 *
 * @section Introduction
 *
 * Software description here
 */


/** @file QSoftMotionPlanner.h
 * @brief Declaration of the QSoftMotionPlanner class
 */
#ifdef ENABLE_DISPLAY
namespace Ui {
    class QSoftMotionPlanner;
}
#endif
/** @brief API of SoftMotion
 *
 */
class QSoftMotionPlanner
#ifdef ENABLE_DISPLAY
:  public QMainWindow, public Ui_MainWindow  {
  Q_OBJECT
#else
    {
#endif

public:
    /** @brief Constructor
     *
     * The constructor of class QSoftMotionPlanner
     *
     * @param *parent : Null
     */
#ifdef ENABLE_DISPLAY
    QSoftMotionPlanner(QWidget *parent = 0);
#else
    QSoftMotionPlanner();
#endif

    /** @brief Destructor
     *
     * The destructor of class QSoftMotionPlanner
     */
    ~QSoftMotionPlanner();

     /** @brief setDisplay
     *
     *  only at startup of the program , if display == flase
     *  the Qt interface is not launched
     *
     * @param val : bool value
     */
    void setDisplay(bool val) {
      _display = val;
    }

    void maxProfile(std::vector<SM_CURVE_DATA>  &ApproxTraj, double *max_jerk, double *max_acc, double *max_vel);

    bool display() {
      return _display;
    }

    /** @brief compute the approximation of a given svg file
     *
     * @param jmax : maximum jerk (m/s^3)
     * @param amax : maximum acceleration (m/s^2)
     * @param vmax : maximum velocity (m/s)
     * @param sampTime : discretisation time (second)
     * @param ErrMax : maximum error of the trajectory allowed
     * @param ExpTime : discretisation of the generated file
     * @param flagExport : genere the result file (true: yes, false: no)
     * @param fileptr : the svg file to approximate
     * @param errTraj : the trajectory error result
     * @param result : the trajectory result
     */
    int approximate(double jmax,double amax,double vmax,double sampTime, double ErrMax, int ExpTime, bool flagExport, FILE* fileptr, double errTraj, std::vector<SM_OUTPUT> result);

    /** @brief load the file
     *
     * load a file .svg
     *
     * @param str : file name
     */
    void loadSvgFile(std::string str);


    /** @brief definition of lines
     *
     * represent a line defined by y = y0 + (x-x0) * (y1-y0)/(x1-x0)
     */
    void defineFunction_l();

    /** @brief definition of circles
     *
     * represent a circle defined by x = a*cos(2*PI*f*t); y = a*sin(2*PI*f*t);
     */
    void defineFunction_c();

    /** @brief definition of sinusoid
     *
     * represent a sinus defined by y = a*sin(2*PI*f*t + phi)
     */
    void defineFunction_s();

    /** @brief definition of parabolic
     *
     * represent a parabolic defined by y = ax^2
     */
    void defineFunction_p();

    void defineFunction_lccl();

    /** @brief initialisation
     *
     * initialize all variables needed for MainWindow
     */
    void initializeApproxVariables();

 #ifdef ENABLE_DISPLAY
public slots:
#endif

    void choose_curve();
    /** @brief open a file
     *
     * open a  .svg file
     */
    void openFile();

    /** @brief close a file
     *
     * close a opened file .svg
     */
    void closeFile();

    /** @brief fullscreen mode
     *
     * maximize the MainWindow using F11 key
     */
    void fullScreen();

    /** @brief computation of the approximated trajectory
     *
     * compute the approximated trajectory if a theorical
     * trajectory is already loaded
     */
    void computeTraj();
    void computeTrajInAdvance();

    /** @brief computation of SoftMotion
     *
     * compute the canonical softMotion trajectory between the
     * two specified initial and final kinematic conditions
     */
    void computeSoftMotion();

    /** @brief generate a data file
     *
     * export the discretized approximated trajectory into a file
     * with a specified sampling time ( 10 ms by default)
     */
    void genFileTraj();

    void genPlotFile();

    /** @brief computation of hausdorff distance
     *
     * compute the hausdorff distance between the ideal and
     * approximated trajectory
     */
    void computeHausdorff();

    /** @brief display a traced trajectory
     *
     * turn on/off the display of a traced trajectory
     */
    void setDraw();

    /** @brief Reset the planner
     *
     * clear all computed and loaded trajectories
     */
    void resetPlanner();

    /** @brief Clear all graphs
     *
     *  clear all the graphs in the qt interface
     */
#ifdef ENABLE_DISPLAY
    void clearPlot();
#endif

      protected:
#ifdef ENABLE_DISPLAY
    void changeEvent(QEvent *e);
#endif

private:
    MyPlot _plot;
    int _nbCurve;
    int _flag_haus_actif;
    std::vector<Curve> _curve; // stocker la trajectoire ideale et approxime
    std::vector<kinPoint> _vec_kinpoint;// les points pour exporter dans le fichier SmDiscr.dat
    std::vector<double> _err_traj;
    std::vector<double> _err_vit;
    std::vector<double> _err_haus1;
    std::vector<double> _err_haus2;
//     std::vector<double> _t_Mlaw,_u_Mlaw,_du_Mlaw,_ddu_Mlaw;
    SM_LIMITS _lim;
    double _errMax;
    double _sampling;// temps d'echantionnage
    int _timeStep;// interval pour generer le fichier
    std::string _fileName;
    bool _isFullScreen;
    bool _display;


};

#endif // QSOFTMOTIONPLANNER_H
