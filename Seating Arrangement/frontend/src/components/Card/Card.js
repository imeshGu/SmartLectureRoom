import React, { useEffect, useContext } from "react";
import Aos from "aos";
import "aos/dist/aos.css";
import "./Card.css";
import { AuthContext } from "../../context/AuthContext";
import axios from "axios";

const Card = (props) => {
    
    const auth = useContext(AuthContext); 
    const { id,
            inv_pro_name,
            sku,
            inv_img,
            inv_pro_description,
            inv_pro_cost,
            inv_pro_selling,
            inv_pro_warranty,
            inv_pro_quantity,
            inv_pro_reorder_level } = props;

    useEffect(() => {
        Aos.init({ duration: 500 });
    }, []);

    const addToCart = async (e) => {
        let update;

        e.preventDefault();
        const cartItem = {
            inventoryItemId: id,
        };

        const config = {
            headers: {
            "x-auth-token": `${auth.token}`,
            "Content-Type": "application/json",
            },
    };

        try {
            update = await axios.put(
            "http://localhost:5000/api/inventory/add_to_cart",
            cartItem,
            config
            );

            if (update) {
            window.alert("Item added to cart");
            }
        } catch (err) {
            console.log(err);
        }
};


  return (
    <div className="card">
      <img
        src={inv_img}      
        alt=""
      />
      <div className="card-content">
        <h2 style={{padding: "10px", height:"60px"}}>{inv_pro_name}</h2>
        {/* <div className="description-row">
          <p>{inv_pro_description}</p>
        </div> */}
        <div className="content-row">
          <p>{inv_pro_selling}</p>
          <p>{sku}</p>
          <svg
            xmlns="http://www.w3.org/2000/svg"
            height="1em"
            viewBox="0 0 576 512"
            onClick={addToCart}
          >
            <path d="M0 24C0 10.7 10.7 0 24 0H69.5c22 0 41.5 12.8 50.6 32h411c26.3 0 45.5 25 38.6 50.4l-41 152.3c-8.5 31.4-37 53.3-69.5 53.3H170.7l5.4 28.5c2.2 11.3 12.1 19.5 23.6 19.5H488c13.3 0 24 10.7 24 24s-10.7 24-24 24H199.7c-34.6 0-64.3-24.6-70.7-58.5L77.4 54.5c-.7-3.8-4-6.5-7.9-6.5H24C10.7 48 0 37.3 0 24zM128 464a48 48 0 1 1 96 0 48 48 0 1 1 -96 0zm336-48a48 48 0 1 1 0 96 48 48 0 1 1 0-96z" />
          </svg>
        </div>
      </div>
    </div>
  );
};

export default Card;
