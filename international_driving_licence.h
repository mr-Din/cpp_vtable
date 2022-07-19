#pragma once

#include "driving_licence.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class InternationalDrivingLicence {
public:
    InternationalDrivingLicence()
        : dl_()
        , table_prt_(&InternationalDrivingLicence::TABLE)
    {
        std::cout << "InternationalDrivingLicence::Ctor()"sv << std::endl;
    }

    InternationalDrivingLicence(const InternationalDrivingLicence& other)
        : dl_(other.dl_)
        , table_prt_(&InternationalDrivingLicence::TABLE)
    {
        std::cout << "InternationalDrivingLicence::CCtor()"sv << std::endl;
    }

    ~InternationalDrivingLicence() {
        if (dl_.table_prt_
            == reinterpret_cast<DrivingLicence::Table*>(&InternationalDrivingLicence::TABLE)) {

            dl_.table_prt_ = &DrivingLicence::TABLE;
        }
        std::cout << "InternationalDrivingLicence::Dtor()"sv << std::endl;
    }

    int GetID() const {
        return dl_.GetID();
    }

    // Для преобразования к базовому типу
    template <typename T>
    operator T() {
        auto ptr = reinterpret_cast<T*>(this);
        dl_.table_prt_ = reinterpret_cast<DrivingLicence::Table*>
            (&DrivingLicence::TABLE);
        return *ptr;
    }

    void PrintID() const {
        std::cout << "InternationalDrivingLicence::PrintID() : "sv << GetID() << std::endl;
    }

    void Delete() {
        this->~InternationalDrivingLicence();
    }

private:
    DrivingLicence dl_;
public:
    // Структура виртуальной таблицы методов
    struct Table
    {
        void (InternationalDrivingLicence::* const PrintID)() const;
        void (InternationalDrivingLicence::* Delete)();
    };
    // Таблица для данного класс
    static Table TABLE;
    // Указатель на таблицу?
    Table* table_prt_;
};

// Определение таблицы
InternationalDrivingLicence::Table InternationalDrivingLicence::TABLE =
{ &InternationalDrivingLicence::PrintID, &InternationalDrivingLicence::Delete };