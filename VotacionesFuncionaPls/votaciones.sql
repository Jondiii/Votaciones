SQLite format 3   @                                                                     -��  � ��e� �                                                                 �'�-tableVOTOSVOTOSCREATE TABLE VOTOS(ID_V INT NOT NULL,ID_P INT NOT NULL,FOREIGN KEY (ID_V) REFERENCES VOTACION(ID_V),FOREIGN KEY (ID_P) REFERENCES PERSONA(ID_P))��[tablePERSONAPERSONACREATE TABLE PERSONA(ID_P INT PRIMARY KEY NOT NULL,EDAD INT,CP CHAR(6),CHECK (EDAD>0),CHECK (EDAD<120))-A indexsqlite_autoindex_PERSONA_1PERSONA�2�3tableCANDIDATOCANDIDATOCREATE TABLE CANDIDATO(ID_C INT PRIMARY KEY NOT NULL,NOMBRE CHAR(30),VOTOS INT DEFAULT 0,ID_VOT INT,FOREIGN KEY (ID_VOT) REFERENCES VOTACION(ID_V))1E indexsqlite_autoindex_CANDIDATO_1CANDIDATO�G�atableVOTACIONVOTACIONCREATE TABLE VOTACION(ID_V INT PRIMARY KEY NOT NULL,NOMBRE TEXT,GANADOR CHAR(30),F_INI INT,F_FIN INT,TIPO_VOTACION CHAR(20),VOT_ABIERTA INT DEFAULT 1,CHECK (F_INI<F_FIN))/C indexsqlite_autoindex_VOTACION_1VOTACION      � ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            		Vot2NADIE1.�4>�N	Vot1NADIE1-�4=�N
   � ��                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           		   � ����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    		iop		pod		Luis	Pepe
   � ����                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 � �                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               	8