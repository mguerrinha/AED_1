#ifndef PROJECT_1_SCHEDULE_INTERFACE_H
#define PROJECT_1_SCHEDULE_INTERFACE_H


#include "ScheduleManager.h"
#include <iostream>

/**
 * @brief Classe que permite interagir com o utilizador.
 */

class Interface {
public:
    Interface();

    static void run();

private:
    /** @brief Objeto que permite obter informações dos horários (seja turma ou uc), dos pedidos e dos estudantes. */
    static ScheduleManager _scheduleManager;

    static int displayMainMenu();

    static int displayConsultarMenu();

    static int displayPedidosMenu();

    static void consultar();

    static void pedidos();

    static void studentInfoMenu();

    static void classInfoMenu();

    static void curriculumInfoMenu();

    static int newRequestMenu();

    static void SubmitNewRequestsMenu(int num_action);
};


#endif //PROJECT_1_SCHEDULE_INTERFACE_H
