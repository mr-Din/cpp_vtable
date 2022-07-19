#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std::string_view_literals;

class Passport {
public:
    Passport()
        : doc_()
        , expiration_date_(GetExpirationDate())
        , table_prt_(&Passport::TABLE)
    {
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>(table_prt_);
        std::cout << "Passport::Ctor()"sv << std::endl;
    }

    Passport(const Passport& other)
        : doc_(other.doc_)
        , expiration_date_(other.expiration_date_)
        , table_prt_(&Passport::TABLE)
    {
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>(table_prt_);
        std::cout << "Passport::CCtor()"sv << std::endl;
    }

    ~Passport() {
        if (doc_.table_prt_
            == reinterpret_cast<IdentityDocument::Table*>(&Passport::TABLE)) {
            
            doc_.table_prt_ = &IdentityDocument::TABLE;
        }
        std::cout << "Passport::Dtor()"sv << std::endl;
    }

    int GetID() const {
        return doc_.GetID();
    }

    void PrintID() const {
        std::cout << "Passport::PrintID() : "sv << GetID();
        std::cout << " expiration date : "sv << expiration_date_.tm_mday << "/"sv << expiration_date_.tm_mon << "/"sv
                  << expiration_date_.tm_year + 1900 << std::endl;
    }

    void PrintVisa(const std::string& country) const {
        std::cout << "Passport::PrintVisa("sv << country << ") : "sv << GetID() << std::endl;
    }

    static void PrintUniqueIDCount() {
        IdentityDocument::PrintUniqueIDCount();
    }

    void Delete() {
        this->~Passport();
    }

    // Для преобразования к базовому типу
    template <typename T>
    operator T() {
        auto ptr = reinterpret_cast<T*>(this);
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>
            (&IdentityDocument::TABLE);
        return *ptr;
    }

private:
    IdentityDocument doc_;

    const struct tm expiration_date_;

    tm GetExpirationDate() {
	    time_t t = time(nullptr);
	    tm exp_date = *localtime(&t);
	    exp_date.tm_year += 10;
	    mktime(&exp_date);
	    return exp_date;
	}


public:
    // Структура виртуальной таблицы методов
    struct Table
    {
        void (Passport::* const PrintID)() const;
        void (Passport::* Delete)();
    };
    // Таблица для данного класс
    static Table TABLE;
    // Указатель на таблицу?
    Table* table_prt_;
};

// Определение таблицы
Passport::Table Passport::TABLE =
{ &Passport::PrintID, &Passport::Delete };