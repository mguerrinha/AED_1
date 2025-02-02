#include "Interface.h"

/**
 * @brief Construtor default da classe Interface.
 */
Interface::Interface() = default;

ScheduleManager Interface::_scheduleManager;

/**
 * @brief Permite correr o programa.
 */
void Interface::run() {
    system("clear");
    _scheduleManager.load_classes("../schedule/classes.csv");
    _scheduleManager.load_students_classes("../schedule/students_classes.csv");
    bool running = true;

    while (running) {
        int choice = displayMainMenu();

        switch (choice) {
            case 1:
                consultar();
                break;

            case 2:
                pedidos();
                break;

            case 9:
                std::cout << "Obrigado pela sua preferência!" << std::endl;
                std::cout << "Prima Enter para terminar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
                running = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

/**
 * @brief Permite mostrar o menu principal.
 * @return Número correspondente à ação que o utilizador pretende realizar.
 */
int Interface::displayMainMenu() {
    int num_action;
    std::cout << "-------------------------- Sistema de Gestão de Horários --------------------------"
              << std::endl;
    std::cout << "Insira o dígito correspondente à operação que pretende realizar!" << std::endl;
    std::cout << "1. Consultas." << std::endl;
    std::cout << "2. Pedidos." << std::endl;
    std::cout << "9. Exit." << std::endl;
    std::cout << ">>> ";
    std::cin >> num_action;
    return num_action;
}

/**
 * @brief Permite mostrar o menu principal de consultas.
 */
void Interface::consultar() {
    system("clear");
    bool running = true;

    while (running) {
        int choice = displayConsultarMenu();
        switch (choice) {
            case 1:
                studentInfoMenu();
                break;

            case 2:
                classInfoMenu();
                break;

            case 3:
                curriculumInfoMenu();
                break;

            case 9:
                running = false;
                system("clear");
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

/**
 * @brief Permite mostrar o menu das oções relacionadas às consultas.
 * @return Número correspondente à ação que o utilizador pretende realizar.
 */
int Interface::displayConsultarMenu() {
    system("clear");
    int num_action;
    std::cout << "----------------- Consultas -----------------" << std::endl;
    std::cout << "1. Informações sobre os alunos." << std::endl;
    std::cout << "2. Informações sobre as turmas." << std::endl;
    std::cout << "3. Informações sobre as unidades curriculares." << std::endl;
    std::cout << "9. Sair." << std::endl;
    std::cout << ">>> ";
    std::cin >> num_action;
    return num_action;
}

/**
 * @brief Permite mostrar o menu das oções relacionadas às informações dos alunos.
 */
void Interface::studentInfoMenu() {
    system("clear");
    bool studenMenuRunning = true;
    int num_aux;
    std::string year;
    unsigned int studentCode;

    while (studenMenuRunning) {
        std::cout << "-------------------- Informações sobre os alunos --------------------" << std::endl;
        std::cout << "1. Horário de um aluno." << std::endl;
        std::cout << "2. Lista e número de alunos num dado ano." << std::endl;
        std::cout << "3. Número de alunos inscritos em pelo menos 'n' unidades curriculares." << std::endl;
        std::cout << "9. Sair." << std::endl;
        std::cout << ">>> ";
        std::cin >> num_aux;
        switch (num_aux) {
            case 1:
                studentCode = _scheduleManager.displayAllStudents();
                _scheduleManager.displayScheduleOfAStudent(studentCode);
                studenMenuRunning = false;
                break;

            case 2:
                year = _scheduleManager.displayClassesYears();
                _scheduleManager.displayStudentsPerYear(year);
                studenMenuRunning = false;
                break;

            case 3:
                int num_uc;
                std::cout << "Insira o 'n' desejado." << std::endl;
                std::cout << ">>> ";
                std::cin >> num_uc;
                _scheduleManager.displayStudentsWithNUcs(num_uc);
                studenMenuRunning = false;
                break;

            case 9:
                studenMenuRunning = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

/**
 * @brief Permite mostrar o menu das oções relacionadas às informações das turmas.
 */
void Interface::classInfoMenu() {
    system("clear");
    bool classMenuRunning = true;
    int num_aux;
    char year;
    std::string classCode, ucCode;
    while (classMenuRunning) {
        std::cout << "-------------------- Informações sobre as turmas --------------------" << std::endl;
        std::cout << "1. Horário de uma turma." << std::endl;
        std::cout << "2. Lista e número de estudantes de uma turma." << std::endl;
        std::cout << "9. Sair." << std::endl;
        std::cout << ">>> ";
        std::cin >> num_aux;
        switch (num_aux) {
            case 1:
                year = _scheduleManager.displayClassesYears();
                classCode = _scheduleManager.displaySomeClasses(year);
                _scheduleManager.displayClassSchedule(classCode);
                classMenuRunning = false;
                break;

            case 2:
                year = _scheduleManager.displayClassesYears();
                classCode = _scheduleManager.displaySomeClasses(year);
                ucCode = ScheduleManager::displaySomeUcs(year);
                _scheduleManager.displayStudentsFromClass(UCSpecificClass(classCode, ucCode));
                classMenuRunning = false;
                break;

            case 9:
                classMenuRunning = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

/**
 * @brief Permite mostrar o menu das oções relacionadas às informações das unidades curriculares.
 */
void Interface::curriculumInfoMenu() {
    system("clear");
    bool curriculumMenuRunning = true;
    int num_aux;
    std::string classCode, ucCode;

    while (curriculumMenuRunning) {
        std::cout << "-------------------- Informações sobre as unidades curriculares --------------------" << std::endl;
        std::cout << "1. Lista e número de estudantes de uma unidade curricular." << std::endl;
        std::cout << "2. Unidade curricular com maior número de alunos." << std::endl;
        std::cout << "3. Horário de uma unidade curricular." << std::endl;
        std::cout << "9. Sair." << std::endl;
        std::cout << ">>> ";
        std::cin >> num_aux;
        switch (num_aux) {
            case 1:
                ucCode = _scheduleManager.displayAllUcs();
                _scheduleManager.displayStudentsFromUC(ucCode);
                curriculumMenuRunning = false;
                break;

            case 2:
                _scheduleManager.displayMostFilledUc();
                curriculumMenuRunning = false;
                break;

            case 3:
                ucCode = _scheduleManager.displayAllUcs();

                std::cout << "A unidade curricular " << ucCode << " tem o seguinte horário:" << std::endl << std::endl;

                _scheduleManager.displayCurriculumSchedule(ucCode);
                curriculumMenuRunning = false;
                break;

            case 9:
                curriculumMenuRunning = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

/**
 * @brief Permite mostrar o menu principal de pedidos.
 */
void Interface::pedidos() {
    system("clear");
    bool running = true;
    int num_action;

    while (running) {
        int choice = displayPedidosMenu();
        switch (choice) {
            case 1:
                num_action = newRequestMenu();
                if (num_action == 9) break;
                SubmitNewRequestsMenu(num_action);
                break;

            case 2:
                _scheduleManager.printPendingRequests();
                break;

            case 3:
                _scheduleManager.processRequests();
                break;
            case 4:
                _scheduleManager.undoLastRequest();
                break;

            case 9:
                system("clear");
                running = false;
                break;

            default:
                std::cout << "Por favor, introduza um dígito válido." << std::endl;
                std::cout << "Prima Enter para continuar.";
                std::cin.ignore();
                std::cin.get();
                system("clear");
        }
    }
}

/**
 * @brief Permite mostrar o menu das oções relacionadas aos pedidos.
 * @return Número correspondente à ação que o utilizador pretende realizar.
 */
int Interface::displayPedidosMenu() {
    system("clear");
    int num_action;
    while (true) {
        std::cout << "-------------- Pedidos --------------" << std::endl;
        std::cout << "1. Submeter novo pedido." << std::endl;
        std::cout << "2. Ver pedidos pendentes." << std::endl;
        std::cout << "3. Processar pedidos." << std::endl;
        std::cout << "4. Anular último pedido." << std::endl;
        std::cout << "9. Sair." << std::endl;
        std::cout << ">>> ";
        std::cin >> num_action;
        if ((num_action >= 1 && num_action <= 4) || num_action == 9) {
            return num_action;
        }
        else {
            std::cout << "Por favor, introduza um dígito válido." << std::endl;
        }
    }
}

/**
 * @brief Permite mostrar o menu das oções relacionadas à submissão de novos pedidos.
 * @return Número correspondente à ação que o utilizador pretende realizar.
 */
int Interface::newRequestMenu() {
    system("clear");
    int num_action;
    while (true) {
        std::cout << "------- Submeter novo pedido -------" << std::endl;
        std::cout << "1. Trocar de turma." << std::endl;
        std::cout << "2. Trocar de Uc." << std::endl;
        std::cout << "3. Inscrição numa nova UC." << std::endl;
        std::cout << "4. Cancelar inscrição numa UC." << std::endl;
        std::cout << "9. Sair" << std::endl;
        std::cout << ">>> ";
        std::cin >> num_action;
        if (num_action >= 1 && num_action <= 4) {
            return num_action;
        }
        else if (num_action == 9) {
            system("clear");
            return num_action;
        }
        else {
            std::cout << "Por favor, introduza um dígito válido." << std::endl;
            std::cout << "Prima Enter para continuar.";
            std::cin.ignore();
            std::cin.get();
            system("clear");
        }
    }
}

/**
 * @brief Permite submeter um novo pedido.
 * @param num_action Número correspondente à ação que o utilizador pretende realizar.
 */
void Interface::SubmitNewRequestsMenu(int num_action) {
    system("clear");
    unsigned int up;
    std::cout << "Insira o número UP do aluno desejado." << std::endl;
    std::cout << ">>> ";
    std::cin >> up;
    Student *student = _scheduleManager.findStudent(up);
    if (student == nullptr) {
        std::cout << "Aluno não encontrado." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    switch (num_action) {
        case 1:
            _scheduleManager.SubmitChangeClassRequest(student);
            break;

        case 2:
            _scheduleManager.SubmitChangeUcRequest(student);
            break;
        case 3:
            _scheduleManager.SubmitEnrollmentRequest(student);
            break;

        case 4:
            _scheduleManager.SubmitRemovalRequest(student);
            break;
        default:
            std::cout << "Por favor, introduza um dígito válido." << std::endl;
            std::cout << "Prima Enter para continuar.";
            std::cin.ignore();
            std::cin.get();
            system("clear");
    }
}







