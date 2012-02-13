/*
 * (c) Copyright 2011 DESY, Eugen Wintersberger <eugen.wintersberger@desy.de>
 *
 * This file is part of libpninx.
 *
 * libpninx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * libpninx is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libpninx.  If not, see <http://www.gnu.org/licenses/>.
 *************************************************************************
 *
 * Definition of a file operation class.
 *
 * Created on: Feb 13, 2012
 *     Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
 */


#ifndef __NXFILEOPS_HPP__
#define __NXFILEOPS_HPP__

namespace pni{
    namespace nx{
        
        template<typename Imp,typename FileType> class NXFileOps{
            private:
                FileType *_file;
            public:
                //============constructors and destructors=====================
                //! default constructor
                NXFileOps():
                    _file(nullptr)
                {
                }

                //! copy constructor
                NXFileOps(const NXFileOps<Imp,FileType> &fops);

                //! move constructor
                NXFileOps(NXFileOps<Imp,FileType> &&fops);

                //! destructor
                ~NXFileOps();

                //===============assignment operators===========================
                //! copy assignment operator
                NXFileOps<Imp,FileType> &
                    operator(const NXFileOps<Imp,FileType> &o);

                //! move assignment operator
                NXFileOps<Imp,FileType> &
                    operator(NXFileOps<Imp,FileType> &&o);

                //================group creation operators======================
                //! create a group

                //! This creates a simple NXGroup object which is given by 
                //! path. If some of the intermediate groups in the path
                //! do not exist they will be created.
                //! \param path path to the new group
                NXGroup<MAPTYPE(Imp,GroupImpl)> mkgroup(const String &path)
                    const;

                //! create a group of a particular type
                
                //! This creates a group of a particular type (Nexus class). 
                //! \param path path to the group to create
                //! \param type nexus class to use
                NXGroup<MAPTYPE(Imp,GroupImpl)> mkgroup(const String &path,const
                        String &type) const;

                //=================field creation operators=====================
                //! create a scalar field
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)> 
                    mkfield(const String &path) const;

                //! create a simpel multidimensional field
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)>
                    mkfield(const String &path,const Shape &s);

                //! create multidimensional field
                template<typename T> NXField<MAPTYPE(Imp,FieldImpl)>
                    mkfield(const String &path,const Shape &s,const Shape &cs);

                //===================linking ==================================
                //! create a link between two objects
                
                //! Creates a link from the object defined by srcpath to the 
                //! location defined by dstpath. If destpath has the form
                //! file:/path an external link will be created. Otherwise
                //! an internal soft-link is established. As with all 
                //! symbolic links the srcpath must not exist at the time
                //! the link is created.
                //! \param srcpath source object
                //! \param dstpath link destination
                void mklink(const String &srcpath,const String &dstpath) const;

                //! create a link between two objects
                
                //! Creates a link from the object given by src to the 
                //! location determined by dstpath. If destpath has the form
                //! file:/path an external link will be created. Otherwise
                //! a local soft link is established.
                //! \param src source object
                //! \param dstpath destination path
                template<typename OImp>
                void mklink(const NXObject<OImp> &src,const String &dstpath)
                const;

                //! create a link

                //! Create an internal soft link from src to location 
                //! group/name determined by the two other arguments.
                //! \param src source object
                //! \param group target group
                //! \param name name of the link below group
                template<typename O1Imp,typename O2Imp>
                    void mklinke(const NXObject<O1mp> &src,const NXGroup<O2Imp>
                            &group,const String &name);

                //==================removing objects===========================
                //! remove object

                //! Removes the link/object refered to by path. If the 
                //! link described by path is a hard-link the object will be
                //! removed from the file. If there are any remaining soft-links
                //! they remain dangling.
                //! \param path object to remove
                void rm(const String &path) const;

                //! remove object
                
                //! Removes object o from the file. 
                template<typename ObjImp> void rm(NXObject<ObjImp> &o) const;
                
                void cp(const String &src,const  String &dest) const;
                template<typename OImp,typename GImp>
                    void cp(const NXObject<OImp> &o,const NXGroup<GImp> &g,const
                            String &name) const;
                

                void mv(const String &src,const  String &dest) const;
                template<typename ObjImp> void
                    mv(NXObject<ObjImp> &o,const String &dest) const;

                template<typename OImp,typename GImp> void
                    mv(NXObject<OImp> &o,const NXGroup<GImp> &group,
                            const String &name) const;


                bool exists(const String &path) const;
                template<typename GImp> bool
                    exists(const NXGroup<GImp> &group,const String &name) const;










        };

    }
}

#endif

