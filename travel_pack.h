#pragma once

#include "identity_document.h"
#include <iostream>
#include <string>

using namespace std::string_view_literals;

class TravelPack {
public:
    TravelPack()
        : doc_()
        , identity_doc1_(reinterpret_cast<IdentityDocument*>(new Passport()))
        , identity_doc2_(reinterpret_cast<IdentityDocument*>(new DrivingLicence()))
        , table_prt_(&TravelPack::TABLE)
    {
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>(table_prt_);
        std::cout << "TravelPack::Ctor()"sv << std::endl;
    }

    TravelPack(const TravelPack& other)
        : doc_(other.doc_)
        , identity_doc1_(reinterpret_cast<IdentityDocument*>
            (new Passport(*reinterpret_cast<Passport*>(other.identity_doc1_))))
        , identity_doc2_(reinterpret_cast<IdentityDocument*>
            (new DrivingLicence(*reinterpret_cast<DrivingLicence*>(other.identity_doc2_))))
        , additional_pass_(other.additional_pass_)
        , additional_dr_licence_(other.additional_dr_licence_) 
        , table_prt_(&TravelPack::TABLE)
    {
        doc_.table_prt_ = reinterpret_cast<IdentityDocument::Table*>(table_prt_);
        std::cout << "TravelPack::CCtor()"sv << std::endl;
    }

    ~TravelPack() {
        // указатель на таблицу базового класса
        if (doc_.table_prt_
            == reinterpret_cast<IdentityDocument::Table*>(&TravelPack::TABLE)) {
            doc_.table_prt_ = &IdentityDocument::TABLE;
        }

        identity_doc1_->Delete();
        identity_doc2_->Delete();
        std::cout << "TravelPack::Dtor()"sv << std::endl;
    }

    void PrintID() const {
        identity_doc1_->PrintID();
        identity_doc2_->PrintID();
        additional_pass_.PrintID();
        additional_dr_licence_.PrintID();
    }

    void Delete() {
        this->~TravelPack();
    }

private:
    IdentityDocument doc_;

    IdentityDocument* identity_doc1_;
    IdentityDocument* identity_doc2_;
    Passport additional_pass_;
    DrivingLicence additional_dr_licence_;

public:
    // Структура виртуальной таблицы методов
    struct Table
    {
        void (TravelPack::* const PrintID)() const;
        void (TravelPack::* Delete)();
    };
    // Таблица для данного класс
    static Table TABLE;
    // Указатель на таблицу?
    Table* table_prt_;
};

// Определение таблицы
TravelPack::Table TravelPack::TABLE =
{ &TravelPack::PrintID, &TravelPack::Delete };