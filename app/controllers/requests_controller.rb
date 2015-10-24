class RequestsController < ApplicationController
    def new
        @request = Request.new
    end
    
    def create
         @request=Request.new(params.require(:request).permit(:name,:contact,:content))
    if @request.save
      
    else
      render 'new'
    end
    redirect_to root_path
    end
    
    def show
        @request=Request.find(params[:id])
    end
    
end
