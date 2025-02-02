#include <cmath>
#include <fstream>
#include <sstream>
#include "ScheduleManager.h"

/**
 * @brief Construtor da classe ScheduleManager.
 * Complexidade: O(1).
 */
ScheduleManager::ScheduleManager() = default;

/**
 * @brief Permite carregar as turmas e as aulas de um ficheiro CSV.
 * Complexidade: O(N logN).
 * @param file
 */
void ScheduleManager::load_classes(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;
    std::getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string classCode, ucCode, weekDay, startHour, Duration, classType;
        if (std::getline(linhaStream, classCode, ',')
            && std::getline(linhaStream, ucCode, ',')
            && std::getline(linhaStream, weekDay, ',')
            && std::getline(linhaStream, startHour, ',')
            && std::getline(linhaStream, Duration, ',')
            && std::getline(linhaStream, classType, ',')) {
            classType.pop_back();
            UCSpecificClass ucSpecificClass(classCode, ucCode);
            Lesson lesson(weekDay, std::stof(startHour), std::stof(Duration), classType, ucSpecificClass);

            if (_classes.find(ucSpecificClass) == _classes.end()) {
                _classes[ucSpecificClass] = Class(ucSpecificClass, std::vector<Lesson>{});
            }
            _classes[ucSpecificClass].addLesson(lesson);

        }
    }
}

/**
 * @brief Permite carregar os estudantes e as suas turmas de um ficheiro CSV.
 * Complexidade: O(N logN).
 * @param file
 */
void ScheduleManager::load_students_classes(const std::string &file) {
    std::ifstream arquivo(file);
    std::string linha;

    std::getline(arquivo, linha);

    while (std::getline(arquivo, linha)) {
        std::stringstream linhaStream(linha);
        std::string studentCode, studentName, ucCode, classCode;
        if (std::getline(linhaStream, studentCode, ',')
            && std::getline(linhaStream, studentName, ',')
            && std::getline(linhaStream, ucCode, ',')
            && std::getline(linhaStream, classCode, ',')) {

            classCode.pop_back();
            unsigned studentCodeInt = std::stoi(studentCode);

            if (_students.find(studentCodeInt) == _students.end()) {
                _students.emplace(studentCodeInt, Student(studentCodeInt, studentName));
            }
            _students[studentCodeInt].addTurma(UCSpecificClass(classCode, ucCode));

            auto it = _classes.find(UCSpecificClass(classCode, ucCode));
            if (it != _classes.end()) {
                it->second.addStudent(studentCodeInt);
            }
        }
    }
}

/**
 * @brief Mostra todos os estudantes inscritos.
 * Complexidade: O(N).
 * @return Número de identificação do estudante.
 */
 unsigned int ScheduleManager::displayAllStudents() {
    system("clear");
    std::cout << "Estudantes inscritos" << std::endl;
    std::cout << "--------------------" << std::endl;
    int counter = 0;
    std::map<int, Student> students;
    for (const auto &student: _students) {
        std::cout << ++counter << ". " << student.first << ' ' << student.second.getName() << std::endl;
        students[counter] = student.second;
    }
    int choice;
    while (true) {
        std::cout << std::endl << "Escolha o aluno desejado." << std::endl;
        std::cout << ">>> ";
        std::cin >> choice;
        if (choice > 0 && choice <= counter) {
            system("clear");
            return students[choice].getStudentCode();
        }
        std::cout << "Por favor, introduza um dígito válido." << std::endl;
    }

}

/**
 * @brief Mostra o número de alunos inscritos em pelo menos 'n' unidades curriculares.
 * Complexidade: O(N).
 * @param n
 */
void ScheduleManager::displayStudentsWithNUcs(int n) {
    system("clear");
    unsigned int count = 0;
    for (const auto &student: _students) {
        if (student.second.getTurmas().size() >= n)
            count++;
    }
    std::cout << "Estão inscritos " << count << " alunos em pelo menos " << n << " unidades curriculares." << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra o horário de um aluno.
 * Complexidade: O(N^2).
 * @param up
 */
void ScheduleManager::displayScheduleOfAStudent(unsigned int up) {

    system("clear");
    std::vector<Lesson> lessonsOfWeek;
    for (const auto &turmas: _students[up].getTurmas()) {
        for (const auto &aula: _classes[turmas].getLessons()) {
            lessonsOfWeek.push_back(aula);
        }
    }

    std::sort(lessonsOfWeek.begin(), lessonsOfWeek.end());

    std::cout << "Horário do aluno " << up << " - " << _students.at(up).getName() << std::endl;
    std::cout << "---------------------------------------------" << std::endl;

    int currentDay = -1;

    for (const Lesson &lesson: lessonsOfWeek) {
        if (lesson.getDayValue() != currentDay) {
            currentDay = lesson.getDayValue();
            std::cout << lesson.getWeekDay() << ":" << std::endl;
        }

        std::cout << ScheduleManager::normalizeHours(lesson.getStartTime()) << " to "
                  << ScheduleManager::normalizeHours(lesson.getStartTime() + lesson.getDuration()) << " -> "
                  << lesson.getUcSpecificClass().getClassCode() << ' '
                  << ucCodeToName(lesson.getUcSpecificClass().getUcCode()) << " ("
                  << lesson.getUcType() << ")" << std::endl;
    }
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra o horário de uma turma.
 * Complexidade: O(N^2).
 * @param classCode
 */
void ScheduleManager::displayClassSchedule(const std::string &classCode) {
    system("clear");
    std::vector<Lesson> lessonsOfClass;

    for (const auto &pair: _classes) {
        UCSpecificClass key = pair.first;
        Class value = pair.second;
        if (key.getClassCode() == classCode) {
            for (const Lesson &lesson: value.getLessons()) {
                lessonsOfClass.push_back(lesson);
            }
        }
    }
    std::sort(lessonsOfClass.begin(), lessonsOfClass.end());

    int currentDay = -1;
    std::cout << "A turma " << classCode << " tem o seguinte horário:" << std::endl << std::endl;
    for (const Lesson &lesson: lessonsOfClass) {
        if (lesson.getDayValue() != currentDay) {
            currentDay = lesson.getDayValue();
            std::cout << lesson.getWeekDay() << ":" << std::endl;
        }

        std::cout << ScheduleManager::normalizeHours(lesson.getStartTime()) << " to "
                  << ScheduleManager::normalizeHours(lesson.getStartTime() + lesson.getDuration()) << " -> "
                  << lesson.getUcSpecificClass().getClassCode() << ' '
                  << ucCodeToName(lesson.getUcSpecificClass().getUcCode()) << " ("
                  << lesson.getUcType() << ")" << std::endl;
    }
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra os alunos pertencentes a uma turma.
 * Complexidade: O(N + N logN).
 * @param ucClass
 */
void ScheduleManager::displayStudentsFromClass(const UCSpecificClass &ucClass) {
    system("clear");
    std::set<Student> students;
    for (auto id: _classes[ucClass].getStudentsIDs()) {
        students.insert(_students[id]);
    }
    ScheduleManager::displaySortedStudents(students);
    std::cout << "Students: " << students.size() << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra o horário de uma unidade curricular.
 * Complexidade: O(N^2).
 * @param ucCode
 */
void ScheduleManager::displayCurriculumSchedule(const std::string &ucCode) {

    std::vector<Lesson> lessonsOfUc;

    for (const auto &pair: _classes) {
        UCSpecificClass key = pair.first;
        Class value = pair.second;
        if (key.getUcCode() == ucCode) {
            for (const Lesson &lesson: value.getLessons()) {
                lessonsOfUc.push_back(lesson);
            }
        }
    }
    std::sort(lessonsOfUc.begin(), lessonsOfUc.end());
    int currentDay = -1;

    for (const Lesson &lesson: lessonsOfUc) {
        if (lesson.getDayValue() != currentDay) {
            currentDay = lesson.getDayValue();
            std::cout << lesson.getWeekDay() << ":" << std::endl;
        }

        std::cout << ScheduleManager::normalizeHours(lesson.getStartTime()) << " to "
                  << ScheduleManager::normalizeHours(lesson.getStartTime() + lesson.getDuration()) << " -> "
                  << lesson.getUcSpecificClass().getClassCode() << ' '
                  << ucCodeToName(lesson.getUcSpecificClass().getUcCode()) << " ("
                  << lesson.getUcType() << ")" << std::endl;
    }
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra os alunos de uma unidade curricular específica.
 * Complexidade: O(N^2 + N logN).
 * @param ucCode
 */
void ScheduleManager::displayStudentsFromUC(const std::string &ucCode) {
    system("clear");
    std::set<Student> students;
    for (auto &it: _classes) {
        if (it.first.getUcCode() == ucCode) {
            for (auto &studentID: it.second.getStudentsIDs()) {
                students.insert(_students[studentID]);
            }
        }
    }
    ScheduleManager::displaySortedStudents(students);
    std::cout << "Students: " << students.size() << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra os alunos do ano desejado, percorrendo todas as turmas.
 * Complexidade: O(N^2 + N logN).
 * @param year
 */
void ScheduleManager::displayStudentsPerYear(const std::string &year) {
    system("clear");
    std::set<Student> students_per_year;

    for (const auto &pair: _classes) {
        if (pair.first.getClassCode().find(year) == 0) {
            for (unsigned int id: pair.second.getStudentsIDs()) {
                students_per_year.insert(_students[id]);
            }
        }
    }
    ScheduleManager::displaySortedStudents(students_per_year);
    std::cout << "O " << year << "º ano é composto por " << students_per_year.size() << " alunos." << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Mostra todas as unidades curriculares disponíveis.
 * Complexidade: O(N).
 * @return Nome correspondente à unidade curricular.
 */
std::string ScheduleManager::displayAllUcs() {
    system("clear");
    std::cout << "Unidades Curriculares" << std::endl;
    std::cout << "---------------------" << std::endl;

    std::set<std::string> ucs;
    int choice;
    int counter = 0;
    std::map<int, std::string> mapping;

    for (auto &it: _classes) {
        ucs.insert(it.first.getUcCode());
    }
    for (auto &uc: ucs) {
        std::cout << ++counter << ". " << uc << " (" << ucCodeToName(uc) << ")" << std::endl;
        mapping[counter] = uc;
    }
    while (true) {
        std::cout << "Escolha a unidade curricular desejada." << std::endl;
        std::cout << ">>> ";
        std::cin >> choice;
        if (choice > 0 && choice <= counter) {
            system("clear");
            return mapping[choice];
        }
        std::cout << "Por favor, introduza um código válido." << std::endl;
    }
}

/**
 * @brief Mostra algumas unidades curriculares consoante o ano.
 * Complexidade: O(N).
 * @param ano
 * @return Unidadades curriculares daquele ano.
 */
std::string ScheduleManager::displaySomeUcs(const char &ano) {
    system("clear");
    std::cout << "Unidades Curriculares da turma" << std::endl;
    std::cout << "---------------------" << std::endl;

    int counter = 0;
    std::map<int, std::string> mapping;
    int choice;

    for (const auto &ucCode: UcsOfAClasse(ano)) {
        std::cout << ++counter << ". " << ucCode << " (" << ucCodeToName(ucCode) << ")" << std::endl;
        mapping[counter] = ucCode;
    }
    std::string ucCode;
    while (true) {
        std::cout << "Escolha a unidade curricular desejada." << std::endl;
        std::cout << ">>> ";
        std::cin >> choice;
        if (choice > 0 && choice <= counter) {
            system("clear");
            return mapping[choice];
        }
        std::cout << "Por favor, introduza um código válido." << std::endl;
    }
    system("clear");
}

/**
 * @brief Mostra algumas turmas consoante o ano.
 * Complexidade: O(N).
 * @param ano
 * @return Turmas daquele ano.
 */
std::string ScheduleManager::displaySomeClasses(const char &ano) {
    system("clear");
    std::cout << "Turmas do " << ano << "º ano" << std::endl;
    std::cout << "-----------------" << std::endl;

    int choice;
    int counter = 0;
    std::map<int, std::string> mapping;
    std::set<std::string> classes;

    for (auto &turma: _classes) {
        if (turma.first.getClassCode()[0] == ano) {
            classes.insert(turma.first.getClassCode());
        }
    }
    for (auto &turma: classes) {
        std::cout << ++counter << ". " << turma << std::endl;
        mapping[counter] = turma;
    }

    while (true) {
        std::cout << std::endl << "Escolha a turma desejada." << std::endl;
        std::cout << ">>> ";
        std::cin >> choice;
        if (choice > 0 && choice <= counter) {
            system("clear");
            return mapping[choice];
        }
        std::cout << "Por favor, introduza um dígito válido." << std::endl;
    }
}

/**
 * @brief Mostra a unidade curricular com mais alunos.
 * Complexidade: O(N).
 */
void ScheduleManager::displayMostFilledUc() {
    system("clear");
    std::map<std::string, unsigned> ucs;
    for (const auto &turma: _classes) {
        ucs[turma.first.getUcCode()] += turma.second.getStudentsIDs().size();
    }
    std::string mostFilledUc;
    unsigned mostFilledUcSize = 0;
    for (const auto &it: ucs) {
        if (it.second > mostFilledUcSize) {
            mostFilledUc = it.first;
            mostFilledUcSize = it.second;
        }
    }
    std::cout << "Unidade Curricular com mais alunos: " << mostFilledUc << std::endl;
    std::cout << "Número de alunos: " << mostFilledUcSize << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Permite normalizar as horas.
 * Complexidade: O(1).
 * @param horas
 * @return Horas normalizadas.
 */
std::string ScheduleManager::normalizeHours(float horas) {
    int hour = static_cast<int>(horas);
    int minutes = static_cast<int>((horas - hour) * 60);

    std::ostringstream formattedTime;
    formattedTime << std::setw(2) << std::setfill('0') << hour << ":" << std::setw(2) << std::setfill('0') << minutes;

    return formattedTime.str();
}

/**
 * @brief Permite mostrar as unidades curriculares por nome.
 * Complexidade: O(1).
 * @param ucCode
 * @return Nome da unidadade curricular.
 */
std::string ScheduleManager::ucCodeToName(const std::string &ucCode) {
    std::map<std::string, std::string> ucs = {{"UP001",    "PUP"},
                                              {"L.EIC001", "ALGA"},
                                              {"L.EIC002", "AM I"},
                                              {"L.EIC003", "FP"},
                                              {"L.EIC004", "FSC"},
                                              {"L.EIC005", "MD"},
                                              {"L.EIC011", "AED"},
                                              {"L.EIC012", "BD"},
                                              {"L.EIC013", "F II"},
                                              {"L.EIC014", "LDTS"},
                                              {"L.EIC015", "SO"},
                                              {"L.EIC021", "FSI"},
                                              {"L.EIC022", "IPC"},
                                              {"L.EIC023", "LBAW"},
                                              {"L.EIC024", "PFL"},
                                              {"L.EIC025", "RC"}};
    return ucs[ucCode];
}

/**
 * @brief Organiza as unidades curriculares por ano.
 * Complexidade: O(1).
 * @param ano
 * @return Vetor com as unidades curriculares do ano desejado.
 */
std::vector<std::string> ScheduleManager::UcsOfAClasse(const char &ano) {
    std::map<char, std::vector<std::string>> ucOfClass = {{'1', {"UP001",    "L.EIC001", "L.EIC002", "L.EIC003", "L.EIC004", "L.EIC005"}},
                                                          {'2', {"L.EIC011", "L.EIC012", "L.EIC013", "L.EIC014", "L.EIC015"}},
                                                          {'3', {"L.EIC021", "L.EIC022", "L.EIC023", "L.EIC024", "L.EIC025"}}};
    return ucOfClass.at(ano);
}

/**
 * @brief Permite encontrar um estudante.
 * Complexidade: O(logN).
 * @param studentCode
 * @return Objeto do tipo Student caso encontrado, nullptr caso contrário.
 */
Student *ScheduleManager::findStudent(unsigned int studentCode) {
    auto it = _students.find(studentCode);
    if (it != _students.end()) {
        return &it->second;
    }
    return nullptr;
}

/**
 * @brief Permite encontrar uma turma.
 * Complexidade: O(logN).
 * @param ucSpecificClass
 * @return Objeto do tipo Class caso encontrado, nullptr caso contrário.
 */
Class *ScheduleManager::findClass(const UCSpecificClass &ucSpecificClass) {
    auto it = _classes.find(ucSpecificClass);
    if (it != _classes.end()) {
        return &it->second;
    }
    return nullptr;
}

/**
 * @brief Verifica a existência de uma unidade curricular.
 * Complexidade: O(N).
 * @param ucCode
 * @return Verdadeiro caso exista, falso caso contrário.
 */
bool ScheduleManager::findUc(const std::string &ucCode) {
    for (const auto &classes: _classes) {
        if (classes.first.getUcCode() == ucCode)
            return true;
    }
    return false;
}

/**
 * @brief Permite obter o número de pedidos pendentes.
 * Complexidade: O(1).
 * @return Número de pedidos pendentes.
 */
int ScheduleManager::getNumOfPendingRequests() const {
    return _changeClassRequests.size() + _enrollmentRequests.size() + _removalRequests.size();
}

/**
 * @brief Permite mostrar todos os pedidos pendentes.
 * Complexidade: O(N).
 */
void ScheduleManager::printPendingRequests() const {
    system("clear");
    if (getNumOfPendingRequests() == 0) {
        std::cout << "Não existem pedidos pendentes." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    std::queue<Requests> pendingChangeClassRequests = _changeClassRequests;
    std::cout << "Pedidos de alteração de turma: " << pendingChangeClassRequests.size() << std::endl;
    while (!pendingChangeClassRequests.empty()) {
        std::cout << pendingChangeClassRequests.front().getStudent().getName()
                  << " | " << pendingChangeClassRequests.front().getStudent().getStudentCode() << std::endl;
        pendingChangeClassRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    std::queue<std::pair<Requests, std::string>> pendingChangeUcRequests = _changeUcRequests;
    std::cout << "Pedidos de alteração de Uc: " << pendingChangeUcRequests.size() << std::endl;
    while (!pendingChangeUcRequests.empty()) {
        std::cout << pendingChangeUcRequests.front().first.getStudent().getName()
                  << " | " << pendingChangeUcRequests.front().first.getStudent().getStudentCode() << std::endl;
        pendingChangeUcRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    std::queue<Requests> pendingEnrollmentRequests = _enrollmentRequests;
    std::cout << "Pedidos de inscrição numa Uc: " << pendingEnrollmentRequests.size() << std::endl;
    while (!pendingEnrollmentRequests.empty()) {
        std::cout << pendingEnrollmentRequests.front().getStudent().getName()
                  << " | " << pendingEnrollmentRequests.front().getStudent().getStudentCode() << std::endl;
        pendingEnrollmentRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    std::queue<Requests> pendingRemovalRequests = _removalRequests;
    std::cout << "Pedidos de cancelamento de inscrição numa Uc: " << pendingRemovalRequests.size() << std::endl;
    while (!pendingRemovalRequests.empty()) {
        std::cout << pendingRemovalRequests.front().getStudent().getName()
                  << " | " << pendingRemovalRequests.front().getStudent().getStudentCode() << std::endl;
        pendingRemovalRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Permite mostrar os pedidos recusados.
 * Complexidade: O(N).
 */
void ScheduleManager::printRejectedRequests() {
    system("clear");
    std::cout << "Pedidos recusados:" << std::endl;
    for (const auto &pair: _rejectedRequests) {
        Requests request = pair.first;
        std::string reason = pair.second;
        std::cout << request.getStudent().getName() << " | " << request.getStudent().getStudentCode()
                  << " ----- Razão: " << reason << std::endl;
    }
    _rejectedRequests.clear();
}

/**
 * @brief Permite submeter um pedido de alteração de turma.
 * Complexidade: O(N + logN).
 * @param student
 */
void ScheduleManager::SubmitChangeClassRequest(Student *student) {
    system("clear");
    std::string ucCode, classCode;
    system("clear");
    std::cout << "--------- Trocar de Turma ---------" << std::endl;
    std::cout << student->getStudentCode() << " - " << student->getName() << std::endl;
    std::cout << "Insira o código da unidade curricular." << std::endl;
    std::cout << ">>> ";
    std::cin >> ucCode;
    if (!findUc(ucCode)) {
        std::cout << "Unidade curricular não encontrada." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    if (!student->isEnrolledUc(ucCode)) {
        std::cout << "O aluno não está inscrito nesta unidade curricular."
                  << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    std::cout << "Insira o código da turma desejada." << std::endl;
    std::cout << ">>> ";
    std::cin >> classCode;
    Class *newClass = findClass(UCSpecificClass(classCode, ucCode));
    if (newClass == nullptr) {
        std::cout << "Turma não encontrada." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    addChangeClassRequest(*student, UCSpecificClass(classCode, ucCode));
    std::cout << "Pedido submetido." << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Permite adicionar a um queue um pedido de alteração de turma.
 * Complexidade: O(1).
 * @param student
 * @param uCSpecificClass
 */
void ScheduleManager::addChangeClassRequest(const Student &student, const UCSpecificClass &uCSpecificClass) {
    _changeClassRequests.emplace(student, uCSpecificClass, "Change Class");
}

/**
 * @brief Permite submeter um pedido de alteração de UC.
 * Complexidade: O(N + logN).
 * @param student
 */
void ScheduleManager::SubmitChangeUcRequest(Student *student) {
    system("clear");
    std::string ucCodeCurrent, ucCodeDesire, classCodeDesired;
    std::cout << "--------- Trocar de unidade curricular ---------" << std::endl;
    std::cout << student->getStudentCode() << " - " << student->getName() << std::endl;
    std::cout << "Insira o código da unidade curricular que quer trocar." << std::endl;
    std::cout << ">>> ";
    std::cin >> ucCodeCurrent;
    if (!findUc(ucCodeCurrent)) {
        std::cout << "Unidade curricular não encontrada.";
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    if (!student->isEnrolledUc(ucCodeCurrent)) {
        std::cout << "O aluno não está inscrito nesta unidade curricular."
                  << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    std::cout << "Insira o código da unidade curricular para a qual deseja trocar." << std::endl;
    std::cout << ">>> ";
    std::cin >> ucCodeDesire;
    if (!findUc(ucCodeDesire)) {
        std::cout << "Unidade curricular não encontrada.";
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    if (student->isEnrolledUc(ucCodeDesire)) {
        std::cout << "O aluno já está inscrito nesta unidade curricular" << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    std::cout << "Insira o código da turma desejada." << std::endl;
    std::cout << ">>> ";
    std::cin >> classCodeDesired;
    Class *newClass = findClass(UCSpecificClass(classCodeDesired, ucCodeDesire));
    if (newClass == nullptr) {
        std::cout << "Turma não encontrada." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    addChangeUcRequest(*student, UCSpecificClass(classCodeDesired, ucCodeDesire), ucCodeCurrent);
    std::cout << "Pedido submetido." << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Permite adicionar a um queue um pedido de alteração de UC.
 * Complexidade: O(1).
 * @param student
 * @param ucSpecificClass
 * @param ucCurrent
 */
void ScheduleManager::addChangeUcRequest(const Student &student, const UCSpecificClass &ucSpecificClass, const std::string &ucCurrent) {
    _changeUcRequests.emplace(Requests(student, ucSpecificClass, "Change Uc"), ucCurrent);
}

/**
 * @brief Permite submeter um pedido de cancelamento de inscrição numa UC.
 * Complexidade: O(N).
 * @param student
 */
void ScheduleManager::SubmitRemovalRequest(Student *student) {
    system("clear");
    std::string ucCode;
    std::cout << "--------- Remover aluno ---------" << std::endl;
    std::cout << student->getStudentCode() << " - " << student->getName() << std::endl;
    std::cout << "Insira o código da unidade curricular." << std::endl;
    std::cout << ">>> ";
    std::cin >> ucCode;
    if (!findUc(ucCode)) {
        std::cout << "Unidade curricular não encontrada.";
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    if (!student->isEnrolledUc(ucCode)) {
        std::cout << "O aluno não está inscrito nesta unidade curricular." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    addRemovalRequest(*student, UCSpecificClass(student->findUCSpecificClass(ucCode).getClassCode(), ucCode));
    std::cout << "Pedido submetido." << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Permite adicionar a um queue um pedido de cancelamento de inscrição numa UC.
 * Complexidade: O(1).
 * @param student
 * @param ucSpecificClass
 */
void ScheduleManager::addRemovalRequest(const Student &student, const UCSpecificClass &ucSpecificClass) {
    _removalRequests.emplace(student, ucSpecificClass, "Removal");
}

/**
 * @brief Permite submeter um pedido de inscrição numa UC.
 * Complexidade: O(N + logN).
 * @param student
 */
void ScheduleManager::SubmitEnrollmentRequest(Student *student) {
    system("clear");
    std::string ucCode, classCode;
    std::cout << "--------- Inscrição em unidade curricular ---------" << std::endl;
    std::cout << student->getStudentCode() << " - " << student->getName() << std::endl;
    std::cout << "Insira o código da unidade curricular." << std::endl;
    std::cout << ">>> ";
    std::cin >> ucCode;
    if (!findUc(ucCode)) {
        std::cout << "Unidade curricular não encontrada.";
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    if (student->isEnrolledUc(ucCode)) {
        std::cout << "O aluno já está inscrito nesta unidade curricular." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    std::cout << "Insira o código da turma desejada." << std::endl;
    std::cout << ">>> ";
    std::cin >> classCode;
    Class *newClass = findClass(UCSpecificClass(classCode, ucCode));
    if (newClass == nullptr) {
        std::cout << "Turma não encontrada." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }
    addEnrollmentRequest(*student, UCSpecificClass(classCode, ucCode));
    std::cout << "Pedido submetido." << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");
}

/**
 * @brief Permite adicionar a um queue um pedido de inscrição numa UC.
 * Complexidade: O(1).
 * @param student
 * @param ucSpecificClass
 */
void ScheduleManager::addEnrollmentRequest(const Student &student, const UCSpecificClass &ucSpecificClass) {
    _enrollmentRequests.emplace(student, ucSpecificClass, "Enrollment");
}

/**
 * @brief Processa os pedidos de cancelamento de inscrição.
 * complexidade: O(N).
 * @param request
 */
void ScheduleManager::processRemovalRequests(const Requests &request) {
    Student *auxStudent = findStudent(request.getStudent().getStudentCode());
    Class *auxClass = findClass(request.getDesiredClass());
    auxStudent->removeTurma(auxClass->getUcClass().getUcCode());
    findClass(auxClass->getUcClass())->removeStudent(auxStudent->getStudentCode());

    _acceptedRequests.emplace(request.getStudent(), request.getDesiredClass(), "Enrollment");
    std::cout << "O aluno " << request.getStudent().getName() << "de número UP" << request.getStudent().getStudentCode()
              << " foi removido da unidade curricular " << request.getDesiredClass().getUcCode() << std::endl;
}

/**
 * @brief Processa os pedidos de inscrição.
 * Complexidade: O(N^2).
 * @param request
 */
void ScheduleManager::processEnrollmentRequests(const Requests &request) {
    Student *student = findStudent(request.getStudent().getStudentCode());
    Class *desiredClass = findClass(request.getDesiredClass());
    for (const auto &turma: student->getTurmas()) {
        if (overlapClasses(turma, desiredClass->getUcClass())) {
            _rejectedRequests.emplace_back(request, "Conflitos com o hoŕario do aluno.");
            return;
        }
    }
    if (exceedsCapacity(request)) {
        _rejectedRequests.emplace_back(request, "Excede o número máximo de alunos permitidos.");
        return;
    } else if (!balancedClasses(request.getDesiredClass(), request.getDesiredClass())) {
        _rejectedRequests.emplace_back(request, "Não favorece o balanceamento das turmas.");
        return;
    } else {
        student->addTurma(request.getDesiredClass());
        findClass(request.getDesiredClass())->addStudent(request.getStudent().getStudentCode());
        std::cout << "O aluno " << request.getStudent().getName() << "de número UP"
                  << request.getStudent().getStudentCode()
                  << " foi inscrito na unidade curricular " << request.getDesiredClass().getUcCode() << std::endl;

        _acceptedRequests.emplace(request.getStudent(), request.getDesiredClass(), "Removal");
    }
}

/**
 * @brief Processa os pedidos de alteração de turma.
 * Complexidade: O(N^2).
 * @param request
 */
void ScheduleManager::processChangeClassRequests(const Requests &request) {
    Student *student = findStudent(request.getStudent().getStudentCode());
    Class *desiredClass = findClass(request.getDesiredClass());
    if (exceedsCapacity(request)) {
        _rejectedRequests.emplace_back(request, "Excede o número máximo de alunos permitidos.");
        return;
    }

    if (!balancedClasses(student->findUCSpecificClass(request.getDesiredClass().getUcCode()),
                         request.getDesiredClass())) {
        _rejectedRequests.emplace_back(request, "Não favorece o balanceamento das turmas.");
        return;
    }

    for (const auto &turma: student->getTurmas()) {
        if (overlapClasses(turma, desiredClass->getUcClass())) {
            _rejectedRequests.emplace_back(request, "Conflitos com o hoŕario do aluno.");
            return;
        }
    }

    std::cout << "O aluno " << request.getStudent().getName() << " com número UP "
              << request.getStudent().getStudentCode() << " na UC "
              << request.getDesiredClass().getUcCode() << " foi movido da turma "
              << student->findUCSpecificClass(request.getDesiredClass().getUcCode()).getClassCode()
              << " para a turma " << request.getDesiredClass().getClassCode();
    student->changeTurma(request.getDesiredClass());
    findClass(student->findUCSpecificClass(request.getDesiredClass().getUcCode()))->removeStudent(
            student->getStudentCode());
    desiredClass->addStudent(student->getStudentCode());

    _acceptedRequests.emplace(request.getStudent(),
                              request.getStudent().findUCSpecificClass(request.getDesiredClass().getUcCode()),
                              "SwitchClass");
}

/**
 * @brief Processa os pedidos de alteração de UC.
 * Complexidade: O(N^2).
 * @param request
 * @param ucCurrent
 */
void ScheduleManager::processChangeUcRequests(const Requests &request, const std::string &ucCurrent) {
    Student *student = findStudent(request.getStudent().getStudentCode());
    Class *desiredClass = findClass(request.getDesiredClass());
    if (exceedsCapacity(request)) {
        _rejectedRequests.emplace_back(request, "Excede a capacidade máxima.");
        return;
    } else if (!balancedClasses(request.getDesiredClass(), request.getDesiredClass())) {
        _rejectedRequests.emplace_back(request, "Não favorece o balanceamento das turmas.");
        return;
    }

    for (const auto &turma: student->getTurmas()) {
        if (overlapClasses(turma, desiredClass->getUcClass())) {
            _rejectedRequests.emplace_back(request, "Conflitos com o hoŕario do aluno.");
            return;
        }
    }

    std::cout << "O aluno " << request.getStudent().getName() << " com número UP "
              << request.getStudent().getStudentCode() << " mudou da Uc "
              << ucCurrent << " para a Uc "
              << request.getDesiredClass().getUcCode() << " para a turma "
              << request.getDesiredClass().getClassCode();
    student->removeTurma(ucCurrent);
    student->addTurma(UCSpecificClass(request.getDesiredClass()));
    findClass(UCSpecificClass(ucCurrent, request.getDesiredClass().getUcCode()))->removeStudent(
            student->getStudentCode());
    desiredClass->addStudent(student->getStudentCode());

    //add to acceptedRequests stack the inverse request
    _acceptedRequests.emplace(request.getStudent(), request.getStudent().findUCSpecificClass(ucCurrent),
                              "SwitchUC");

}

/**
 * @brief Processa todos os pedidos, dando print dos pedidos aceites e recusados.
 * @see processRemovalRequests().
 * @see processEnrollmentRequests().
 * @see processChangeClassRequests().
 * @see processChangeUcRequests().
 * @see printRejectedRequests().
 * @see UpdateStudentsClassesCSV().
 */
void ScheduleManager::processRequests() {
    system("clear");

    if (_removalRequests.empty() && _changeUcRequests.empty() && _enrollmentRequests.empty() && _changeClassRequests.empty()) {
        std::cout << "Nada para ser processado." << std::endl;
        std::cout << "Prima Enter para continuar.";
        std::cin.ignore();
        std::cin.get();
        system("clear");
        return;
    }

    std::cout << "Pedidos de cancelamento de inscrição aceites:" << std::endl;

    while (!_removalRequests.empty()) {
        processRemovalRequests(_removalRequests.front());
        _removalRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    std::cout << "Pedidos de inscrição aceites:" << std::endl;

    while (!_enrollmentRequests.empty()) {
        processEnrollmentRequests(_enrollmentRequests.front());
        _enrollmentRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    std::cout << "Pedidos de alteração de turma aceites:" << std::endl;
    while (!_changeClassRequests.empty()) {
        processChangeClassRequests(_changeClassRequests.front());
        _changeClassRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    std::cout << "Pedidos de alteração de Uc aceites:" << std::endl;
    while (!_changeUcRequests.empty()) {
        processChangeUcRequests(_changeUcRequests.front().first, _changeUcRequests.front().second);
        _changeUcRequests.pop();
    }

    std::cout << "-------------------------------------------------" << std::endl << std::endl;

    if (!_rejectedRequests.empty()) {
        printRejectedRequests();
    } else {
        std::cout << "Todos os pedidos foram aceites." << std::endl;
    }
    std::cout << "-------------------------------------------------" << std::endl << std::endl;
    std::cout << "Prima Enter para continuar.";
    std::cin.ignore();
    std::cin.get();
    system("clear");

    UpdateStudentsClassesCSV();
}

/**
 * @brief Verifica se duas turmas têm horários sobrepostos.
 * Complexidade: O(N^2).
 * @param ucSpecificClass
 * @param ucSpecificClassDesired
 * @return Verdadeiro caso não haja sobreposição, falso caso contrário.
 */
bool ScheduleManager::overlapClasses(const UCSpecificClass &ucSpecificClass, const UCSpecificClass &ucSpecificClassDesired) {
    std::vector<Lesson> lessons1 = _classes.at(ucSpecificClass).getLessons();
    std::vector<Lesson> lessons2 = _classes.at(ucSpecificClassDesired).getLessons();
    for (const auto &l1: lessons1) {
        for (const auto &l2: lessons2) {
            if (l1.isOverlapping(l2))
                return false;
        }
    }
    return true;
}

/**
 * @brief Verifica se uma turma excede a capacidade máxima.
 * Complexidade: O(1).
 * @param request
 * @return Verdadeiro caso não exceda, falso caso contrário.
 */
bool ScheduleManager::exceedsCapacity(const Requests &request) {
    if (_classes.at(request.getDesiredClass()).getStudentsIDs().size() >= maxCapacity(request.getDesiredClass()))
        return true;
    return false;
}

/**
 * @brief Permite obter a capacidade máxima permitida.
 * Complexidade: O(1).
 * @param ucSpecificClass
 * @return Capacidade máxima permitida.
 */
unsigned int ScheduleManager::maxCapacity(const UCSpecificClass &ucSpecificClass) {
    return 30;
}

/**
 * @brief Verifica se uma turma favorece o balanceamento das turmas.
 * Complexidade: O(N).
 * @param ucSpecificClass
 * @param ucSpecificClassDesired
 * @return Verdadeiro caso favoreça, falso caso contrário.
 */
bool ScheduleManager::balancedClasses(const UCSpecificClass &ucSpecificClass,
                                      const UCSpecificClass &ucSpecificClassDesired) {

    if (desvioClasses(ucSpecificClass) < 4 && desvioAfterChange(ucSpecificClass, ucSpecificClassDesired,
                                                                _classes.at(ucSpecificClass).getStudentsIDs().size() -
                                                                1, _classes.at(
                    ucSpecificClassDesired).getStudentsIDs().size() + 1) > 4) {
        return false;
    } else if (desvioClasses(ucSpecificClass) < 4 && desvioAfterChange(ucSpecificClass, ucSpecificClassDesired,
                                                                       _classes.at(
                                                                               ucSpecificClass).getStudentsIDs().size() -
                                                                       1, _classes.at(
                    ucSpecificClassDesired).getStudentsIDs().size() + 1) < 4) {
        return true;
    } else if (desvioClasses(ucSpecificClass) > desvioAfterChange(ucSpecificClass, ucSpecificClassDesired,
                                                                  _classes.at(ucSpecificClass).getStudentsIDs().size() -
                                                                  1, _classes.at(
                    ucSpecificClassDesired).getStudentsIDs().size() + 1)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Calcula o desvio padrão das turmas.
 * Complexidade: O(N).
 * @param ucSpecificClass
 * @return Desvio padrão das turmas.
 */
double ScheduleManager::desvioClasses(const UCSpecificClass &ucSpecificClass) {
    double media = 0, i = 0;
    for (const auto &classes: _classes) {
        if (classes.first == ucSpecificClass) {
            media += (double) _classes.at(ucSpecificClass).getStudentsIDs().size();
        } else if (classes.first.getUcCode() == ucSpecificClass.getUcCode()) {
            media += (double) classes.second.getStudentsIDs().size();
        }
        i++;
    }
    media /= i;
    double desvio = 0;
    for (const auto &classes: _classes) {
        if (classes.first.getUcCode() == ucSpecificClass.getUcCode()) {
            desvio += std::pow((double) classes.second.getStudentsIDs().size() - media, 2);
        }
    }
    return std::sqrt(desvio / i);
}

/**
 * @brief Calcula o desvio padrão das turmas após uma alteração.
 * Complexidade: O(N).
 * @param ucSpecificClass
 * @param ucSpecificClassDesired
 * @param sizeClass
 * @param sizeClassDesired
 * @return Desvio padrão das turmas após uma alteração.
 */
double ScheduleManager::desvioAfterChange(const UCSpecificClass &ucSpecificClass,
                                          const UCSpecificClass &ucSpecificClassDesired, const unsigned int &sizeClass,
                                          const unsigned int &sizeClassDesired) {
    double media = 0, i = 0;
    for (const auto &classes: _classes) {
        if (classes.first == ucSpecificClass) {
            media += (double) sizeClass;
            i++;
        } else if (classes.first == ucSpecificClassDesired) {
            media += (double) sizeClassDesired;
            i++;
        } else if (classes.first.getUcCode() == ucSpecificClass.getUcCode()) {
            media += (double) classes.second.getStudentsIDs().size();
            i++;
        } else continue;
    }
    media /= i;
    double desvio = 0;
    for (const auto &classes: _classes) {
        if (classes.first == ucSpecificClass) {
            desvio += std::pow((double) sizeClass - media, 2);
        } else if (classes.first == ucSpecificClassDesired) {
            desvio += std::pow((double) sizeClassDesired - media, 2);
        } else if (classes.first.getUcCode() == ucSpecificClass.getUcCode()) {
            desvio += std::pow((double) _classes.at(ucSpecificClass).getStudentsIDs().size(), 2);
        } else continue;
    }
    return std::sqrt(desvio / i);
}

/**
 * @brief Permite mostrar as turmas por ano.
 * Complexidade: O(N).
 * @return Ano da turma.
 */
char ScheduleManager::displayClassesYears() {
    system("clear");
    char ano;
    std::set<char> years;
    for (const auto &pair: _classes) {
        years.insert(pair.first.getClassCode()[0]);
    }
    int counter = 0;
    std::cout << "Anos disponíveis:" << std::endl;
    for (const auto &year: years) {
        std::cout << ++counter << ". " << year << "º ano" << std::endl;
    }
    while (true) {
        std::cout << std::endl << "Insira o ano da turma/estudante" << std::endl;
        std::cout << ">>> ";
        std::cin >> ano;
        if (years.find(ano) != years.end()) {
            system("clear");
            return ano;
        }
        std::cout << "Por favor, insira um dígito válido" << std::endl;
    }
}

/**
 * @brief Permite ordenar a forma de mostrar os alunos.
 * Complexidade: O(N logN).
 * @param students
 */
void ScheduleManager::displaySortedStudents(const std::set<Student> &students) {
    std::cout << "Introduza a ordenação desejada:" << std::endl;
    std::cout << "1. Nome (ascendente)" << std::endl;
    std::cout << "2. Nome (descendente)" << std::endl;
    std::cout << "3. Código UP (ascendente)" << std::endl;
    std::cout << "4. Código UP (descendente)" << std::endl;
    int choice;
    while (true) {
        std::cout << ">>> ";
        std::cin >> choice;
        if (choice > 0 && choice <= 4) {
            break;
        }
        std::cout << "Por favor, introduza um dígito válido." << std::endl;
    }

    std::vector<Student> sorted_students(students.begin(), students.end());

    switch (choice) {
        case 1:
            std::sort(sorted_students.begin(), sorted_students.end(), [](const Student &s1, const Student &s2) {
                return s1.getName() < s2.getName();
            });
            break;
        case 2:
            std::sort(sorted_students.begin(), sorted_students.end(), [](const Student &s1, const Student &s2) {
                return s1.getName() > s2.getName();
            });
            break;
        case 3:
            std::sort(sorted_students.begin(), sorted_students.end(), [](const Student &s1, const Student &s2) {
                return s1.getStudentCode() < s2.getStudentCode();
            });
            break;
        case 4:
            std::sort(sorted_students.begin(), sorted_students.end(), [](const Student &s1, const Student &s2) {
                return s1.getStudentCode() > s2.getStudentCode();
            });
            break;
        default:
            std::cout << "Por favor, introduza um dígito válido." << std::endl;
    }

    for (const auto &student: sorted_students) {
        std::cout << student.getName() << " - up" << student.getStudentCode() << std::endl;
    }
}

/**
 * @brief Atualiza as turmas de um estudante.
 * Complexidade: O(N^2).
 */
void ScheduleManager::UpdateStudentsClassesCSV() {
    std::ofstream file;
    file.open("../schedule/students_classes.csv");
    file << "StudentCode,StudentName,UcCode,ClassCode" << std::endl;
    for (const auto &student: _students) {
        for (const auto &ucSpecificClass: student.second.getTurmas()) {
            file << student.second.getStudentCode() << "," << student.second.getName() << ","
                 << ucSpecificClass.getUcCode() << "," << ucSpecificClass.getClassCode() << "\r\n";
        }
    }
    file.flush();
    file.close();
}

/**
 * @brief Permite voltar atrás no último pedido realizado.
 * @see processEnrollmentRequests().
 * @see processRemovalRequests().
 * @see processChangeClassRequests().
 * @see processChangeUcRequests().
 * @see UpdateStudentsClassesCSV().
 */
void ScheduleManager::undoLastRequest() {
    // Tentar desfazer a última operação na stack _acceptedRequests. Se for bem-sucedido, dar pop. Se não, perguntar ao utilizador se quer abri-la de qualquer forma.
    if (_acceptedRequests.empty()) {
        std::cout << "Não existem pedidos aceites para desfazer." << std::endl;
        return;
    }
    Requests undo = _acceptedRequests.top();
    std::cout << "Desfazer o último pedido irá processar o seguinte pedido:" << std::endl;
    std::cout << "Aluno: " << undo.getStudent().getName() << " - up" << undo.getStudent().getStudentCode() << std::endl;
    std::cout << "Unidade Curricular: " << undo.getDesiredClass().getUcCode() << std::endl;
    std::cout << "Turma: " << undo.getDesiredClass().getClassCode() << std::endl;
    std::cout << "Tipo de pedido: " << undo.gettypeRequest() << std::endl;

    char choice;
    while (true) {
        std::cout << "Deseja desfazer o pedido? (y/n)" << std::endl;
        std::cin >> choice;
        if (choice == 'y') {
            break;
        }
        if (choice == 'n') {
            return;
        }
    }
    Student *student = findStudent(undo.getStudent().getStudentCode());
    Class *desiredClass = findClass(undo.getDesiredClass());
    if (undo.gettypeRequest() == "Enrollment") {
        student->addTurma(undo.getDesiredClass());
        desiredClass->addStudent(undo.getStudent().getStudentCode());
    } else if (undo.gettypeRequest() == "Removal") {
        student->removeTurma(desiredClass->getUcClass().getUcCode());
        desiredClass->removeStudent(student->getStudentCode());
    } else if (undo.gettypeRequest() == "SwitchClass") {
        student->changeTurma(undo.getDesiredClass());
        findClass(student->findUCSpecificClass(undo.getDesiredClass().getUcCode()))->removeStudent(
                student->getStudentCode());
        desiredClass->addStudent(student->getStudentCode());
    } else if (undo.gettypeRequest() == "SwitchUC") {
        student->removeTurma(undo.getDesiredClass().getUcCode());
        student->addTurma(UCSpecificClass(undo.getDesiredClass()));
        findClass(student->findUCSpecificClass(undo.getDesiredClass().getUcCode()))->removeStudent(
                student->getStudentCode());
        desiredClass->addStudent(student->getStudentCode());
    }
    _acceptedRequests.pop();

    UpdateStudentsClassesCSV();
}












