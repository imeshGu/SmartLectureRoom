import React, { useState, useEffect, useContext } from "react";
import { FaBars } from "react-icons/fa";
import { IconContext } from "react-icons/lib";
import { useNavigate } from "react-router-dom";
import {
  Nav,
  NavbarContainer,
  MobileIcon,
  NavMenu,
  NavBtnLink,
  NavLinks,
  NavLogo,
} from "./NavbarElements";

const Navbar = ({ toggle }) => {
  const [scrollNav, setScrollNav] = useState(false);
  const navigate = useNavigate();

  const changeNav = () => {
    if (window.scrollY >= 80) {
      setScrollNav(true);
    } else {
      setScrollNav(false);
    }
  };

  useEffect(() => {
    window.addEventListener("scroll", changeNav);
  }, []);

  const signOut = () => {
    // auth.logout();
    navigate("/home");
    window.location.reload();
  };

  return (
    <>
      <IconContext.Provider value={{ color: "#fff" }}>
        <Nav scrollNav={scrollNav}>
          <NavLogo to="/">SeatSync</NavLogo>
          <NavbarContainer>
            <MobileIcon onClick={toggle}>
              <FaBars />
            </MobileIcon>
            <NavLinks
              to="/"
              smooth={true}
              duration={500}
              spy={true}
              exact="true"
              offset={-80}
            >
              Home
            </NavLinks>

            <NavMenu>
              <NavBtnLink
                className="btn btn-outline-danger m-2"
                onClick={signOut}
              >
                Logout
              </NavBtnLink>

              {/* <NavBtnLink className="btn btn-outline-danger m-2" to="/login">
                Sign In
              </NavBtnLink> */}
            </NavMenu>
          </NavbarContainer>
        </Nav>
      </IconContext.Provider>
    </>
  );
};

export default Navbar;
