# import sqlite3
import datetime
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import relationship
from sqlalchemy import Table, Column, Integer, ForeignKey, String, DateTime
from sqlalchemy import create_engine
from sqlalchemy.orm import sessionmaker
Base = declarative_base()


class Osoba(Base):
    __tablename__ = 'Osoba'
    id = Column(Integer, primary_key=True)
    imie = Column(String(20), nullable=False)
    wiek = Column(Integer, default=18)
    created = Column(DateTime, default=datetime.datetime.utcnow)
    adresy = relationship('Adres')

    def __repr__(self):
        return "<Osoba(imie='%s', wiek='%s', created='%s')>" % (
                            self.imie, self.wiek, self.created)


class Adres(Base):
    __tablename__ = 'Adresy'
    id = Column(Integer, primary_key=True)
    email = Column(String)
    miasto = Column(String)
    mieszkaniec = Column(Integer, ForeignKey("Osoba.id"))


# db = sqlite3.connect("/tmp/temp.db")
engine = create_engine('sqlite:///wyklad.db', echo=False)
Base.metadata.create_all(engine)
Session = sessionmaker(bind=engine)
sesja = Session()


def dodaj_debesciaka():
    o = Osoba(imie='Debeściak')
    adr1 = Adres(email='Joliot@Curie', miasto='Wrocław')
    o.adresy = [adr1]
    sesja.add(o)
    sesja.add(adr1)
    sesja.commit()


# dodaj_debesciaka()
# lista = sesja.query(Osoba).filter(Osoba.imie.in_(['Debeściak'])).all()
lista = sesja.query(Osoba).filter_by(imie='Debeściak').all()
for obiekt in lista:
    print(obiekt)